The hv_driver takes input 14 bits of data(first 2 bits are 0 followed by 12 bits of the conversion result) from the ADC((ADS7044) and converts it to an equivalent high voltage
that it represents. 

Note: The input is in 2’s complement format. The ADC value of 4043 corresponds to HV voltage reading of 168V and the ADC value of -3288 is 125V. 
 
In order to test the code, the behavior of an ADC is simuated in the file sys_main.c. MIBSPIREG1 is enabled as a master and MIBSPIREG3 which is simulating the ADC is the Slave.
A adcVoltageRamp function is implemented in sys_main.c that is used for ramping up and down the measured voltage simulated by the ADC. These random test values are then passed 
to the hv_driver to get the corresponding voltage it represents. 
