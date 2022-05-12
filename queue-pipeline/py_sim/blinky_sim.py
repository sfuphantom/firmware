from functools import partial
from time import time
from tkinter import W
from sim import Simulation

class BlinkySimulation(Simulation):

    @property
    def init_cmd(self):
        return '1,1'

    @property
    def parser_config(self):
        return [
                ['led', 'LED one'],
            ]
    
    def construct_serial(self, args):
        led = args['led']
        print(led)
        return '{},{}'.format(int('1' in led), int('2' in led))

    def print_help(self):
        console_out = ''
        console_out += 'optional arguments:\n'
        console_out += '\t-h, --help  show this help message and exit\n'
        console_out += '\t-e, --exit  Exit program\n'
        print(console_out)

if __name__ == '__main__':
    blinky_sim = BlinkySimulation('COM7')
    blinky_sim.run()

