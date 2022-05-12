from blinky_sim import BlinkySimulation
test_sim = BlinkySimulation('COM7')
def print_test(curr_val:str, reset=False):

    if reset:
        print_test.count = 1
        return
    to_print = curr_val.strip('\n')
    print(to_print, print_test.count, end='\r')
    print_test.count += 1

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


if __name__ == '__main__':
        
    test_actor_logic()

