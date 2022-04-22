/*
 * RTD.h
 *
 *  Created on: Feb 3, 2022
 *      Author: Adam Tinaburri
 */

#ifndef RTD_H_
#define RTD_H_

#include "sys_vim.h"
#include "sys_common.h"
#include "gio.h"


void RTDInit();
bool isBreakPressed(); // checks if the break is being pressed
bool TSALstatus(); // checks if tractive system is active


#endif /* RTD_H_ */
