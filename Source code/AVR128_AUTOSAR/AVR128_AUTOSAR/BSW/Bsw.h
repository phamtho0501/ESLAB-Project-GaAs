/*
 * Bsw.h
 *
 * Created: 7/17/2022 11:32:39 PM
 *  Author: ThoPH
 */ 


#ifndef BSW_H_
#define BSW_H_

#include <avr/io.h>
#include <stdlib.h>
#include <string.h>
#include "floatToString.h"
#include <PHT_LCD16x2_4bit.h>
#include <BSW_UART.h>
#include "liquid_crystal_i2c.h"
#include <adc.h>
#include <util/delay.h>

extern LiquidCrystalDevice_t device;

void BSW_driverInit(void);

#endif /* BSW_H_ */