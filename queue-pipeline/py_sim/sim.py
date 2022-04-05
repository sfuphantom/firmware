import queue
import threading
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
        self.ser = Serial(port = port, baudrate = 9600, bytesize = EIGHTBITS, stopbits = STOPBITS_TWO, timeout = 10)
        self.q = queue.Queue()

    @abstractmethod
    def construct_serial(self, args):
        pass
    
    @property
    @abstractmethod
    def parser_config(self):
        pass

    @property
    @abstractmethod
    def init_cmd(self):
        pass
    
    def send_serial(self):
        print(self.init_cmd)
        serial_msg = self.init_cmd
        while True:

            try:
                serial_msg = self.q.get(block=False, timeout=0.1)
            except queue.Empty:
                pass
            
            # -1 signals a shutdown
            if serial_msg == -1:
                break

            self.ser.write(bytes(serial_msg, encoding='utf8'))
            time.sleep(0.3)

    def run(self):
     
        serial_thread = threading.Thread(target=self.send_serial)
        serial_thread.daemon = True
        serial_thread.start()
       
        while True:
            # grab user input
            cmd = input('>>> ')

            # construct argument parser
            parser = argparse.ArgumentParser()
            parser.add_argument('-e','--exit', help='Exit program', action='store_true')
            parser_config = self.parser_config
            for i in range(len(parser_config)):
                cmd_config = parser_config[i]
                flag1, flag2, help_msg, action = cmd_config 
                parser.add_argument(flag1, flag2, help=help_msg, action=action)

            # parse arguments and update serial message 
            args = vars(parser.parse_args(cmd.split()))

            if args['exit']:
                print('Exiting simulation...')
                self.q.put(-1)
                break
            
            serial_msg = self.construct_serial(args)
            self.q.put(serial_msg)
            time.sleep(0.1)

        serial_thread.join()
        
        

