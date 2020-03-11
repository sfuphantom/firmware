
//#include "sys_common.h"
#include "i2c.h"
//#include "het.h"
//#include "gio.h"
//#include "stdlib.h"
//#include "sci.h"



#define LV_DATA_COUNT  2

#define LV_Slave_Address  0x40


//Register
#define LV_configuration_register 0x00
#define LV_Shunt_register 0x01
#define LV_bus_voltage_register 0x02
#define LV_calibration_register 0x05
#define LV_current_register 0x04
#define LV_power_register 0x03


void lv_monitorInit();
//need to initalize i2c before using


int LV_reading(uint16_t mode);
/*
list of input for mode to get reading.
1. LV_Shunt_register
2. LV_bus_voltage_register
3. LV_current_register
4. LV_power_register

//ex. code
to read bus voltage
int LV_reading(LV_bus_voltage_register);

to read current
LV_reading(LV_current_register);


*/
