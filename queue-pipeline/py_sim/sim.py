# Created by Rafael Guevara
from asyncio import QueueEmpty
from functools import partial
import queue
import threading
from tkinter.tix import Tree
from typing import Callable, Iterable
from serial import (
    Serial,
    EIGHTBITS,
    STOPBITS_TWO
)
import time
from abc import ABC, abstractmethod
import argparse

class Simulation(ABC):

    ser: Serial

    def __init__(self, port) -> None:
        self.ser = Serial(port=port, baudrate = 9600, bytesize = EIGHTBITS, stopbits = STOPBITS_TWO, timeout=1)
        self.q_serial_send = queue.Queue()
        self.q_serial_receive = queue.Queue()
        self.q_test = queue.Queue() 
        
    @abstractmethod
    def construct_serial(self, args):
        '''
        Provide a recipe for constructing the serial message
        from a dictionary of the user's inputs
        '''
        pass
    
    @property
    @abstractmethod
    def parser_config(self):
        '''
        Provide a 2D array representing the list of commands to argparse
        '''
        pass

    @property
    @abstractmethod
    def init_cmd(self):
        '''
        Return the initial value sent to the MCU on startup
        '''
        pass
    
    def send_serial(self):
        serial_msg = self.init_cmd
        while True:

            try:
                serial_msg = self.q_serial_send.get(block=False, timeout=0.1)
            except queue.Empty:
                pass
            
            # -1 signals a shutdown
            if serial_msg == -1:
                break
            self.ser.write(bytes(serial_msg, encoding='utf8'))
            time.sleep(0.1)

    def receive_serial(self, expected_value:int=None, logger_fn:Callable=lambda x: None):
        curr_val = None
        while True:
            q_msg = ''
            try:
                q_msg = self.q_serial_receive.get(block=False, timeout=0.1)
            except queue.Empty:
                pass
            
            # -1 signals a shutdown
            if q_msg == -1:
                break
            # read from board
            msg = self.ser.readline().decode()
            msg = 0
            if msg != '':
                curr_val = int(msg)
            logger_fn(curr_val, expected_value)
            if q_msg == 1:
                self.q_test.put(curr_val)
        
            # if in validation mode, signal a pass
            if expected_value is not None and (curr_val == expected_value):
                self.q_test.put(1)
                break
            time.sleep(0.3)

    def prompt(self):
        # grab user input
        cmd = input('>>> ')

        # construct argument parser
        parser = argparse.ArgumentParser()
        parser.add_argument('-e','--exit', help='Exit program', action='store_true')
        parser_config = self.parser_config
        for i in range(len(parser_config)):
            cmd_config = parser_config[i]
            pos_arg, help_msg  = cmd_config 
            parser.add_argument(pos_arg, help=help_msg)

        # parse arguments and update serial message 
        return vars(parser.parse_args(cmd.split()))

    def run(self):

        serial_thread = threading.Thread(target=self.send_serial, daemon=True)
        serial_thread.daemon = True
        serial_thread.start()

        while True:
            try: 
                args = self.prompt()
            except SystemExit:
                continue

            user_input = args['led']
            if user_input == 'exit':
                print('Exiting simulation...')
                self.q_serial_send.put(-1)
                break
            elif user_input == 'echo':
                echo_val = self.ser.read_all().decode().split('\n')[-2]
                print(f'Serial value: {echo_val}')
                continue

            serial_msg = self.construct_serial(args)
            self.q_serial_send.put(serial_msg)
            time.sleep(0.1)

        serial_thread.join()
        
        
    def test_serial(self, sim_values:Iterable, expected_value:int, timeout=10, logger_fn:Callable=lambda x: None, period=0.1):
        '''
        Run through all 'sim_values' at 'period' and wait until
        received value == 'expected_value', unless 'timeout'
        '''
        # start simulation thread
        serial_thread = threading.Thread(target=self.send_serial, daemon=True)
        serial_thread.start()

        # simulate values
        for value in sim_values:
            self.q_serial_send.put(value)
            time.sleep(period)

        validate_period = 0.1
        # wait for success
        iterations = int(timeout / validate_period)        
        for _ in range(iterations):
            msg = self.ser.readline().decode()
            logger_fn(msg)
            if msg != '' and int(msg) == expected_value:
                self.q_serial_send.put(-1)
                serial_thread.join()
                return True
            time.sleep(validate_period)

        self.q_serial_send.put(-1)
        serial_thread.join()
        return False
