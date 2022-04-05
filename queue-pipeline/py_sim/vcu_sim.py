from sim import Simulation

class VCUSimulation(Simulation):

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


vcu_sim = VCUSimulation('COM7')

vcu_sim.run()
