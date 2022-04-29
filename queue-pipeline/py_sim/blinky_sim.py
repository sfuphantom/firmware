from sim import Simulation

class BlinkySimulation(Simulation):

    @property
    def init_cmd(self):
        return '1,1'

    @property
    def parser_config(self):
        return [
                    ['-a','--led1', 'LED one', 'store_true'],
                    ['-d','--led2', 'LED two', 'store_true']
            ]
    
    def construct_serial(self, args):
        return '{},{}'.format(int(args['led1']), int(args['led2']))

    def print_help(self):
        console_out = ''
        console_out += 'optional arguments:\n'
        console_out += '\t-h, --help  show this help message and exit\n'
        console_out += '\t-e, --exit  Exit program\n'
        console_out += '\t-a, --led1  LED one\n'
        console_out += '\t-d, --led2  LED two'
        print(console_out)

blinky_sim = BlinkySimulation('COM7')


blinky_sim.run_lambda()

