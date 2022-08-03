/*
 * adc.h
 *
 * Created: 7/17/2022 11:14:02 PM
 *  Author: ThoPH
 */ 


#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>
#include <Std_Type.h>

#ifndef F_CPU
#define F_CPU 7372800UL
#endif

#define CHANEL_SETTING(n)   (n & 0x07)

void f_setchanel(uint8 chanel);
void f_adc_init(void);
uint16 f_read_adc(void);

#endif /* ADC_H_ */