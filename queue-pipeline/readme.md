# Queue Pipeline

This project acts as a template/prototype for a general purpose redesign of
microcontroller firmware at Team Phantom. The design emphasizes isolated, ```single responsibility``` modules connected together through queues. The code is implemented in C using freeRTOS.

## Software Architecture

The diagram below illustrates a software system with three major types of tasks: Directors, Actors, and Agents. These tasks communicate through freeRTOS queues depcited by the mailboxes in the diagram. Solid black arrows indicate signals to and from the outside world, while the solid blue arrows act as control signals to the other tasks. Data travels up the pipeline starting from the Agent and ending with the Director. The Actors are blocked from executing until data is passed to them from their Agents. Because of this close dependency, each collection of Actors and Agents can be thought of as a single Task Module.

![](/diagrams/QueuePipeline.svg)

* ### ```Director(s):``` Orchestrates the state of other tasks; normally the role of the state machine
* ### ```Actors:``` Where most of the software logic is contained; they act on the data that is given to them and pass the transformed information to the Director and/or output signals to the real world
* ### ```Agents:``` Their role is to communicate with the outside world and provide data for the Actors to act upon 

## Simulation Mode

Using this new architecture, we can strip and then mimic the Agents to test the Actors and Directors. Next to no code will need to be modified in these tasks to make this possible. This makes testing simpler, provides simulation closer to the final product, and allows software and firmware development to happen in parallel; Agent work can be tested with with real hardware, and Actor work can be tested in this mode.

In this mode, all Agents are replaced by a single Simulation Agent connected to a Python script mimicing all of the sensor data. Here, only one hardware peripheral has to be implemented: UART. Comparing this diagram to the one above shows that everything above the Agents is left completely untouched and is therefore almost entirely agnostic to the mode that is currently being run.  

![](/diagrams/SimulationMode.svg)

## Debug Mode

This mode acts complimentary to simulation mode. This does not replace any code, but instead adds a Debug Actor to process messages passed from other tasks and output them to USB through UART. This can either be viewed through the serial terminal or captured by another program for command lines, data analysis, or automated testing.

![](/diagrams/DebugMode.svg)

# Source Code

## MCU code

* ### [Common folder](/common/README.md) 
* ### [Agent](/tasks/Agent1/README.md)
* ### [Actor](/tasks/Actor/README.md) 
* ### [Director](/tasks/Director/README.md)

## Simulation 

* ### [PySerial program](/py_sim/README.md)
* ### [Simulation task](/tasks/TaskSim/README.md)
* ### [Debug task](/tasks/taskUART/README.md)