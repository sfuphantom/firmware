/*
 * phantom_vcu.h
 *
 *  Created on: Feb 25, 2020
 *      Author: XingLu Wang
 */

#ifndef INCLUDE_PHANTOM_CAN_H_
#define INCLUDE_PHANTOM_CAN_H_
#include "stdint.h"

void CANSend(uint8_t can_msg[]);
char getBMSMSG(void);


#endif /* INCLUDE_PHANTOM_CAN_H_ */
