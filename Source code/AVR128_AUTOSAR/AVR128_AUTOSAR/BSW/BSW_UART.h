/*
 * BSW_UART.h
 *
 * Created: 8/1/2022 11:17:17 PM
 *  Author: ThoPH
 */ 


#ifndef BSW_UART_H_
#define BSW_UART_H_


#include <UART.h>

#define UART0_Init(baudrate) UART_Init(C_UartZero_U8,  baudrate)
#define UART1_Init(baudrate) UART_Init(C_UartOne_U8,   baudrate)

#define UART0_TxChar(ch) UART_TxChar(C_UartZero_U8,  ch)
#define UART1_TxChar(ch) UART_TxChar(C_UartOne_U8,   ch)

#define UART0_RxChar() UART_RxChar(C_UartZero_U8)
#define UART1_RxChar() UART_RxChar(C_UartOne_U8)

#define UART0_TxString(ptr) UART_TxString(C_UartZero_U8,  ptr)
#define UART1_TxString(ptr) UART_TxString(C_UartOne_U8,   ptr)

#define UART0_RxString(ptr) UART_RxString(C_UartZero_U8,  ptr)
#define UART1_RxString(ptr) UART_RxString(C_UartOne_U8,   ptr)

#define UART0_TxNumber(NumberSystem, Number, NoOfDigits)  UART_TxNumber(C_UartZero_U8,  NumberSystem, Number, NoOfDigits)
#define UART1_TxNumber(NumberSystem, Number, NoOfDigits)  UART_TxNumber(C_UartOne_U8,   NumberSystem, Number, NoOfDigits)

#define UART0_TxFloatNumber(Number)  UART_TxFloatNumber(C_UartZero_U8,  Number)
#define UART1_TxFloatNumber(Number)  UART_TxFloatNumber(C_UartOne_U8,   Number)

#define UART0_Printf(var_arg_list...) UART_Printf(C_UartZero_U8,  var_arg_list)
#define UART1_Printf(var_arg_list...) UART_Printf(C_UartOne_U8,   var_arg_list)

void UART_TxString(uint8 var_uartChannel_u8, uint8 *ptr_stringPointer_u8);
void UART_RxString(uint8 var_uartChannel_u8, uint8 *ptr_stringPointer_u8);
void UART_TxNumber(uint8 var_uartChannel_u8, uint8 var_numericSystem_u8, uint32 var_number_u32, uint8 var_numOfDigitsToTransmit_u8);
void UART_TxFloatNumber(uint8 var_uartChannel_u8, float32 var_floatNumber_f32);
void UART_Printf(uint8 var_uartChannel_u8, const uint8 *argList, ...);

#endif /* BSW_UART_H_ */