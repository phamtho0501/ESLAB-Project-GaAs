/*
 * UART.c
 *
 * Created: 7/17/2022 11:30:29 PM
 *  Author: ThoPH
 */ 

#include <stdarg.h>
#include "UART.h"

#define C_MaxUartChannels_U8 2u
#define C_UartOne_U8         1u

void UART_Init(uint8 var_uartChannel_u8, uint32 var_baudRate_u32)
{    
    switch(var_uartChannel_u8)
    {
    case 0:
	
        UCSR0B= (1<<RXEN) | (1<<TXEN);                  
        UCSR0C = (0<<USBS)|(1<<UCSZ1)|(1<<UCSZ0); 
        UCSR0A= 0x00;                                   
        UART_SetBaudRate(var_uartChannel_u8,var_baudRate_u32);
        break;


    case 1:
	    
        UCSR1B= (1<<RXEN) | (1<<TXEN);                 
        UCSR1C= (1<<UCSZ1) | (1<<UCSZ0);   
        UCSR1A= 0x00;                                   
        UART_SetBaudRate(var_uartChannel_u8,var_baudRate_u32);
        break;

    }



}
void UART_SetBaudRate(uint8 var_uartChannel_u8, uint32 var_baudRate_u32)
{
    uint16 RegValue;
    if((var_baudRate_u32 >= C_MinBaudRate_U32) && (var_baudRate_u32<=C_MaxBaudRate_U32))
    {
        RegValue = M_GetBaudRateGeneratorValue(var_baudRate_u32);
    }
    else
    {
        RegValue = M_GetBaudRateGeneratorValue(9600);
    }
    switch(var_uartChannel_u8)
    {
    case 0:
        UBRR0L = util_ExtractByte0to8(RegValue);
        UBRR0H = util_ExtractByte8to16(RegValue);
        break;
    case 1:
        UBRR1L = util_ExtractByte0to8(RegValue);
        UBRR1H = util_ExtractByte8to16(RegValue);
        break;
    }  



}

uint8 UART_RxChar(uint8 var_uartChannel_u8)
{
    uint8 s1a_data;
	
	s1a_data = 0; 

    switch(var_uartChannel_u8)
    {
    case 0:
        while(util_IsBitCleared(UCSR0A,RXC));  
        s1a_data = UDR0;

        break;


    case 1:
        while(util_IsBitCleared(UCSR1A,RXC));  
        s1a_data = UDR1;
        break;

    }
    return s1a_data;    
}

void UART_TxChar(uint8 var_uartChannel_u8, uint8 var_uartData_u8)
{
    switch(var_uartChannel_u8)
    {
    case 0:
        while(util_IsBitCleared(UCSR0A,UDRE)); 
        UDR0 =var_uartData_u8;

        break;


    case 1:
        while(util_IsBitCleared(UCSR1A,UDRE)); 
        UDR1 =var_uartData_u8;
        break;

    }
}


