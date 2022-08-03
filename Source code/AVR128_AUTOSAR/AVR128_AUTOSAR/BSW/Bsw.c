/*
 * Bsw.c
 *
 * Created: 7/17/2022 11:33:18 PM
 *  Author: ThoPH
 */ 

#include <Bsw.h>

LiquidCrystalDevice_t device;

static void IO_Init();
//static void LCD_Init(LiquidCrystalDevice_t* module);
static void f_uartInit(void);

void IO_Init(){
	DDRE = 0xFF;
	DDRD |= (1<<PD4)|(1<<PD5);
	
	PORTE = 0x00;
	PORTD &= ~((1<<PD4)|(1<<PD5));
}

// void LCD_Init(LiquidCrystalDevice_t* module) {
// 	*module = lq_init(0x27, 16, 2, LCD_5x8DOTS);
// 	lq_turnOnBacklight(module);
// }

void f_uartInit(void) {
	UART1_Init(9600);
	return;
}

void BSW_driverInit(void)
{
	IO_Init();
	//LCD_Init(&device);
	lcd_init();
	f_setchanel(0u);
	f_adc_init();
	f_uartInit();
	return;
}