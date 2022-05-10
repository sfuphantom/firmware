# Queue Pipeline

This project acts as a template/prototype for a general purpose redesign of any
microcontroller firmware in Team Phantom. The design patterns used here are applicable to any real time software system and emphasize isolated Single Responsibility software modules connected together through queues. The code is implemented in C using freeRTOS.

## Software Architecture

The diagram below illustrates a software system with three major types of tasks: Directors, Actors, and Agents. These tasks communicate through freeRTOS queues depcited by the mailboxes in the diagram. Solid black arrows indicate signals to and from the outside world, while the solid blue arrows act as control signals to the other tasks. Each collection of Actors and Agents can be thought of as a Task Module. 


![](/diagrams/QueuePipeline.svg)

* Directors: Orchestrate the other tasks; normally the role of the state machine
* Actors: Where most of the software logic is contained; they act on the data that is given to them and pass the transformed information to the Director and/or output signals to the real world
* Agents: Their role is to communicate with the outside world and provide data for the Actors to act upon 

## Design Benefits

As mentioned above, a big reason for this design is to isolate pieces of code and provide defined interfaces for each task. This makes it easier to debug while also allowing ease of simulation without straying too far from the final product.

## Simulation Mode

Using this new architecture, we can strip and then mimic the Agents to test the Actors and Directors. Next to no code will need to be modified in these tasks to make this possible. This makes testing simpler, provides simulation closer to the final product, and allows software and firmware development to happen in parallel; Agent work can be tested with sensors, and Actor work can be tested with this mode.

In this mode, all Agents are replaced by a single Simulation Agent connected to a Python script mimicing all of the sensor data. Here, only one hardware peripheral has to be implemented: UART. There is often very good support for USB communication with the PC out of the box on development boards. Comparing this diagram to the one above shows that everything above the Agents is left untouched. 

![](/diagrams/SimulationMode.svg)

## Debug Mode

This mode acts complimentary to simulation mode. This does not replace any code, but instead adds a Debug Actor to process messages passed from other tasks and outputs them through UART. This can either be viewed through the serial terminal or captured by another python script for data analysis, or automated testing.

![](/diagrams/DebugMode.svg)

# Source Code

## MCU code

* ### [Common folder](/common/) 
* ### [Agent](/tasks/Agent1/)
* ### [Actor](/tasks/Actor/) 
* ### [Director](/tasks/Director/)

## Simulation 

* ### [PySerial program](/py_sim/)
* ### [Simulation task](/tasks/TaskSim/)
* ### [Debug task](/tasks/taskUART/)
  
## C Unit Tests

* ### [Basic unit testing](/unit_tests/)