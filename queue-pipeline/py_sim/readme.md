# sim.py
This class uses argparse, serial, and the threading modules to implement a command line interface that can take input from the user and send data to the MCU simultaneously. It is an abstract base class with three abstract methods.

Multithreading was used so that values are sent consistently to the MCU by the python script in between test values or user input.
```
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
```

## Blinky Simulation
The BlinkySimulation implements this class and will...

* ```init_cmd```: initially transmit '1,1' before any user input
* ```parser_config```: hold one command for the cli to switch on led1 or led2 
* ```construct_serial```: take the arguments parsed by argparse and send it to the MCU as led1_value,led2_value
* ```print_help```: print the following message when the user types 'help'

Once the class has been defined, all that must be done is to initialize the correct port, and call blinky_sim.run(). This will allow you to run a command line and change sensor values on the fly.
```
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
```

# Automated Testing 
A huge benefit from this tool is the ability to automatically send values and validate their results in a real time fashion. 

Here is a collection of basic tests generated with only a few lines of code. These test that the system can respond to sensor inputs in a timely manner and output the correct result ('and' gate output).

```
def test_serial(self, sim_values:Iterable, expected_value:int, timeout=10, logger_fn:Callable=lambda x: None, period=0.1):
    '''
    Run through all 'sim_values' at 'period' and wait until
    received value == 'expected_value', unless 'timeout'
    '''
```

```
def test_actor_logic():

    print_test(None, True)
    print('Test 1')
    assert test_sim.test_serial(['0,0'], 0, logger_fn=print_test, period=1)
    print("\npass!")

    print_test(None, True)
    print('Test 2')
    assert test_sim.test_serial(['0,1'], 0, logger_fn=print_test, timeout=5, period=1)
    print("\npass!")

    print_test(None, True)
    print('Test 3')
    assert test_sim.test_serial(['1,0'], 0, logger_fn=print_test, period=1)
    print("\npass!")

    print_test(None, True)
    print('Test 4')
    assert test_sim.test_serial(['1,1'], 1, logger_fn=print_test, timeout=10, period=1)
    print("\npass!")
```

### [back to root](/README.md) 



