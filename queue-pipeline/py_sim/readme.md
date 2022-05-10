# sim.py
This class uses argparse, serial, and the threading modules to implement a command line interface that can take input from the user and send data to the MCU simultaneously. It is an abstract base class with three abstract methods. Explaining the implementation of the non-abstract methods is outside the scope and/or relevance of this project. Please contact me if you have any questions.


```
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
```

## Blinky Simulation
The BlinkySimulation will...

* init_cmd: initially transmit '1,1' before any user input
* parser_config: hold two commands for the cli -a and -d to signal switching on led1 or led2 respectively
* construct_serial: take the arguments parsed by argparse and send it to the MCU as led1_value,led2_value
* print_help: print the following message when the user types 'help'

Once the class has been defined, all that must be done is to initialize the correct port, and call blinky_sim.run()

```
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

blinky_sim.run()
```
