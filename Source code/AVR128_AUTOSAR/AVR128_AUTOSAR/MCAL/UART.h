/*
 * UART.h
 *
 * Created: 7/17/2022 11:30:29 PM
 *  Author: ThoPH
 */ 

#ifndef _UART_H_
#define _UART_H_

#include <Std_Type.h>
#include <avr/io.h>
#include "stdutils.h"

#define C_MinBaudRate_U32 2400
#define C_MaxBaudRate_U32 115200UL

#ifndef F_CPU
#define F_CPU 7372800UL
#endif

#define M_GetBaudRateGeneratorValue(baudrate)  ((F_CPU/((baudrate)<<4))-1)               

#define C_UartZero_U8    0u
#define C_UartOne_U8     1u

#define Enable_UART_TxString          1
#define Enable_UART_RxString          1
#define Enable_UART_TxNumber          1
#define Enable_UART_TxFloatNumber     1
#define Enable_UART_Printf            1

#define C_DefaultDigitsToTransmit_U8          0xffu   
#define C_MaxDigitsToTransmit_U8              10u    
#define C_NumOfBinDigitsToTransmit_U8         16u      
#define C_MaxDigitsToTransmitUsingPrintf_U8   C_DefaultDigitsToTransmit_U8 

void UART_Init(uint8 var_uartChannel_u8, uint32 var_baudRate_u32);
void UART_SetBaudRate(uint8 var_uartChannel_u8, uint32 var_baudRate_u32);
void UART_TxChar(uint8 var_uartChannel_u8, uint8 var_uartData_u8);
uint8 UART_RxChar(uint8 var_uartChannel_u8);

#endif




