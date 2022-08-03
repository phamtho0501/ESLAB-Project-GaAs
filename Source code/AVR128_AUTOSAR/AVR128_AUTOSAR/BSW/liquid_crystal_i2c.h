/*
 * liquid_crystal_i2c.h
 *
 * Created: 7/17/2022 11:30:29 PM
 *  Author: ThoPH
 */ 


#ifndef LIQUIDCRYSTALI2CDEVICE_H_
#define LIQUIDCRYSTALI2CDEVICE_H_

#include <avr/io.h>
#include <stdint.h>
#include "i2c.h"

#ifndef  F_CPU
#define F_CPU 8000000UL
#endif

// commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// flags for function set
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00

// flags for backlight control
#define LCD_BACKLIGHT 0x08
#define LCD_NOBACKLIGHT 0x00

#define LCD_ENABLE_BIT 0b00000100  // Enable bit
#define LCD_READ_WRITE_BIT 0b00000010  // Read/Write bit
#define LCD_REGISTER_SELECT_BIT 0b00000001  // Register select bit

typedef struct LiquidCrystalDevice_t {
	uint8 Address;
	uint8 Columns;
	uint8 Rows;
	uint8 Backlight;
	uint8 DisplayFunction;
	uint8 DisplayControl;
	uint8 DisplayMode;
} LiquidCrystalDevice_t;

struct LiquidCrystalDevice_t lq_init(uint8 address, uint8 columns, uint8 rows, uint8 dotSize);

void lq_clear(struct LiquidCrystalDevice_t* device);

void lq_setCursor(struct LiquidCrystalDevice_t* device, uint8 row, uint8 column);

void lq_returnHome(struct LiquidCrystalDevice_t* device);

void lq_turnOnBacklight(struct LiquidCrystalDevice_t* device);

void lq_turnOffBacklight(struct LiquidCrystalDevice_t* device);

void lq_print(struct LiquidCrystalDevice_t* device, sint8* value);

void lq_turnOnDisplay(struct LiquidCrystalDevice_t* device);

void lq_turnOffDisplay(struct LiquidCrystalDevice_t* device);

void lq_turnOnCursor(struct LiquidCrystalDevice_t* device);

void lq_turnOffCursor(struct LiquidCrystalDevice_t* device);

void lq_turnOnBlink(struct LiquidCrystalDevice_t* device);

void lq_turnOffBlink(struct LiquidCrystalDevice_t* device);

void lq_scrollDisplayLeft(struct LiquidCrystalDevice_t* device);

void lq_scrollDisplayRight(struct LiquidCrystalDevice_t* device);

void lq_leftToRight(struct LiquidCrystalDevice_t* device);

void lq_rightToLeft(struct LiquidCrystalDevice_t* device);

void lq_turnOnAutoscroll(struct LiquidCrystalDevice_t* device);

void lq_turnOffAutoscroll(struct LiquidCrystalDevice_t* device);

void lq_createChar(struct LiquidCrystalDevice_t* device, uint8 slot, uint8 charmap[8]);


void lq_sendCommand(struct LiquidCrystalDevice_t* device, uint8 command);

void lq_writeDeviceByte(struct LiquidCrystalDevice_t* device, uint8 value, uint8 mode);

void lq_writeDevice4Bits(struct LiquidCrystalDevice_t* device, uint8 value);

void lq_writeDevicePulse(struct LiquidCrystalDevice_t* device, uint8 value);

void lq_transmitI2C(struct LiquidCrystalDevice_t* device, uint8 value);

#endif /* LIQUIDCRYSTALI2CDEVICE_H_ */