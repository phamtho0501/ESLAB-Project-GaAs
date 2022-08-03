/*
 * adc.c
 *
 * Created: 7/17/2022 11:15:31 PM
 *  Author: ThoPH
 */

#include <adc.h>

static uint8 chanel;

/**
  * @brief  f_reverse
  *         
  * @param
  * @param
  * @retval
  */
void f_setchanel(uint8 chanel) {
	chanel = CHANEL_SETTING(chanel);
}

/**
  * @brief  f_reverse
  *         
  * @param
  * @param
  * @retval
  */
void f_adc_init(void)
{
	ADMUX |= ((1 << REFS0) | chanel);
	ADCSRA |= (1 << ADEN) | (1 << ADPS2) | (1 << ADPS0);
}

/**
  * @brief  f_read_adc
  *         
  * @param
  * @param
  * @retval
  */
uint16 f_read_adc(void)
{
	ADMUX = (ADMUX & 0xF8) | chanel;
	
	ADCSRA |= (1<<ADSC);
	
	while (ADCSRA & (1 << ADSC));
	
	return(ADC);
}