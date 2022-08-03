/*
 * BSW_UART.c
 *
 * Created: 8/1/2022 11:17:06 PM
 *  Author: ThoPH
 */ 

#if (Enable_UART_TxString==1)
void UART_TxString(uint8 var_uartChannel_u8, uint8 *ptr_stringPointer_u8)
{
	while(*ptr_stringPointer_u8)
	UART_TxChar(var_uartChannel_u8, *ptr_stringPointer_u8++);// Loop through the string and transmit char by char
}
#endif

#if (Enable_UART_RxString==1)

void UART_RxString(uint8 var_uartChannel_u8, uint8 *ptr_stringPointer_u8)
{
	uint8 u1a_data;
	
	while(1) {
		/* Get data into register */
		u1a_data = UART_RxChar(var_uartChannel_u8);

		/* Check end of buffer */
		if(('\r' == u1a_data) || ('\n' == u1a_data)) {
			/* Clear the current buffer */
			*ptr_stringPointer_u8 = 0;
			break;
		}
		
		/* Update data to buffer */
		*ptr_stringPointer_u8 = u1a_data;
		/* The next address */
		ptr_stringPointer_u8++;
	}
}
#endif

#if ((Enable_UART_TxNumber==1) || (Enable_UART_TxFloatNumber==1) || (Enable_UART_Printf == 1))
void UART_TxNumber(uint8 var_uartChannel_u8, uint8 var_numericSystem_u8, uint32 var_number_u32, uint8 var_numOfDigitsToTransmit_u8)
{
	uint8 i=0,a[10];

	if(C_BINARY_U8 == var_numericSystem_u8)
	{
		while(var_numOfDigitsToTransmit_u8!=0)
		{
			i = util_GetBitStatus(var_number_u32,(var_numOfDigitsToTransmit_u8-1));
			UART_TxChar(var_uartChannel_u8,util_Dec2Ascii(i));
			var_numOfDigitsToTransmit_u8--;
		}
	}
	else if(var_number_u32==0)
	{

		for(i=0;((i<var_numOfDigitsToTransmit_u8) && (i<C_MaxDigitsToTransmit_U8)) ;i++)
		UART_TxChar(var_uartChannel_u8,'0');
	}
	else
	{
		for(i=0;i<var_numOfDigitsToTransmit_u8;i++)
		{

			if(var_number_u32!=0)
			{

				a[i]=util_GetMod32(var_number_u32,var_numericSystem_u8);
				var_number_u32=var_number_u32/var_numericSystem_u8;
			}
			else if( (var_numOfDigitsToTransmit_u8 == C_DefaultDigitsToTransmit_U8) ||
			(var_numOfDigitsToTransmit_u8 > C_MaxDigitsToTransmit_U8))
			{

				break;
			}
			else
			{

				a[i]=0;
			}
		}

		while(i)
		{
			UART_TxChar(var_uartChannel_u8,util_Hex2Ascii(a[i-1]));
			i--;
		}
	}


}
#endif

#if (Enable_UART_TxFloatNumber==1)
void UART_TxFloatNumber(uint8 var_uartChannel_u8, float32 var_floatNumber_f32)
{
	uint32 var_tempNumber_u32;


	var_tempNumber_u32 = (uint32) var_floatNumber_f32;
	UART_TxNumber(var_uartChannel_u8,C_DECIMAL_U8,var_tempNumber_u32,C_DefaultDigitsToTransmit_U8);

	UART_TxChar(var_uartChannel_u8,'.');

	var_floatNumber_f32 = var_floatNumber_f32 - var_tempNumber_u32;
	var_tempNumber_u32 = var_floatNumber_f32 * 1000000;
	UART_TxNumber(var_uartChannel_u8,C_DECIMAL_U8,var_tempNumber_u32,C_DefaultDigitsToTransmit_U8);
}
#endif

#if ( Enable_UART_Printf   == 1 )
void UART_Printf(uint8 var_uartChannel_u8, const uint8 *argList, ...)
{
	const uint8 *ptr;
	double64 var_floatNum_f32;
	va_list argp;
	sint16 var_num_s16;
	sint32 var_num_s32;
	uint16 var_num_u16;
	uint32 var_num_u32;
	uint8 *str;
	uint8  ch;
	uint8 var_numOfDigitsToTransmit_u8;

	va_start(argp, argList);
	for(ptr = argList; *ptr != '\0'; ptr++)
	{

		ch= *ptr;
		if(ch == '%')
		{
			ptr++;
			ch = *ptr;
			if((ch>=0x30) && (ch<=0x39))
			{
				var_numOfDigitsToTransmit_u8 = 0;
				while((ch>=0x30) && (ch<=0x39))
				{
					var_numOfDigitsToTransmit_u8 = (var_numOfDigitsToTransmit_u8 * 10) + (ch-0x30);
					ptr++;
					ch = *ptr;
				}
			}
			else
			{
				var_numOfDigitsToTransmit_u8 = C_MaxDigitsToTransmitUsingPrintf_U8;
			}


			switch(ch)       /* Decode the type of the argument */
			{

				case 'C':
				case 'c':     /* Argument type is of char, hence read char data from the argp */
				ch = va_arg(argp, sint32);
				UART_TxChar(var_uartChannel_u8,ch);
				break;



				case 'd':    /* Argument type is of signed integer, hence read 16bit data from the argp */
				var_num_s16 = va_arg(argp, sint32);
				#if (Enable_UART_TxNumber == 1)
				if(var_num_s16<0)
				{ /* If the number is -ve then display the 2's complement along with '-' sign */
					var_num_s16 = -var_num_s16;
					UART_TxChar(var_uartChannel_u8,'-');
				}
				UART_TxNumber(var_uartChannel_u8,C_DECIMAL_U8,var_num_s16,var_numOfDigitsToTransmit_u8);
				#endif
				break;



				case 'D':    /* Argument type is of integer, hence read 16bit data from the argp */
				var_num_s32 = va_arg(argp, sint32);
				#if (Enable_UART_TxNumber == 1)
				if(var_num_s32<0)
				{ /* If the number is -ve then display the 2's complement along with '-' sign */
					var_num_s32 = -var_num_s32;
					UART_TxChar(var_uartChannel_u8,'-');
				}
				UART_TxNumber(var_uartChannel_u8,C_DECIMAL_U8,var_num_s32,var_numOfDigitsToTransmit_u8);
				#endif
				break;



				case 'u':    /* Argument type is of unsigned integer, hence read 16bit unsigned data */
				var_num_u16 = va_arg(argp, sint32);
				#if (Enable_UART_TxNumber == 1)
				UART_TxNumber(var_uartChannel_u8,C_DECIMAL_U8,var_num_u16,var_numOfDigitsToTransmit_u8);
				#endif
				break;



				case 'U':    /* Argument type is of integer, hence read 32bit unsigend data */
				var_num_u32 = va_arg(argp, uint32);
				#if (Enable_UART_TxNumber == 1)
				UART_TxNumber(var_uartChannel_u8,C_DECIMAL_U8,var_num_u32,var_numOfDigitsToTransmit_u8);
				#endif
				break;


				case 'x':  /* Argument type is of hex, hence hexadecimal data from the argp */
				var_num_u16 = va_arg(argp, int);
				#if (Enable_UART_TxNumber == 1)
				UART_TxNumber(var_uartChannel_u8,C_HEX_U8, var_num_u16,var_numOfDigitsToTransmit_u8);
				#endif
				break;



				case 'X':  /* Argument type is of hex, hence hexadecimal data from the argp */
				var_num_u32 = va_arg(argp, uint32);
				#if (Enable_UART_TxNumber == 1)
				UART_TxNumber(var_uartChannel_u8,C_HEX_U8, var_num_u32,var_numOfDigitsToTransmit_u8);
				#endif
				break;



				case 'b':  /* Argument type is of binary,Read int and convert to binary */
				var_num_u16 = va_arg(argp, sint32);
				#if (Enable_UART_TxNumber == 1)
				if(var_numOfDigitsToTransmit_u8 == C_MaxDigitsToTransmitUsingPrintf_U8)
				{
					var_numOfDigitsToTransmit_u8 = 16;
				}
				UART_TxNumber(var_uartChannel_u8,C_BINARY_U8, var_num_u16,var_numOfDigitsToTransmit_u8);
				#endif
				break;



				case 'B':  /* Argument type is of binary,Read int and convert to binary */
				var_num_u32 = va_arg(argp, uint32);
				#if (Enable_UART_TxNumber == 1)
				if(var_numOfDigitsToTransmit_u8 == C_MaxDigitsToTransmitUsingPrintf_U8)
				var_numOfDigitsToTransmit_u8 = 16;
				UART_TxNumber(var_uartChannel_u8,C_BINARY_U8, var_num_u32,var_numOfDigitsToTransmit_u8);
				#endif
				break;



				case 'F':
				case 'f': /* Argument type is of float, hence read double data from the argp */
				var_floatNum_f32 = va_arg(argp, double64);
				#if (Enable_UART_TxFloatNumber == 1)
				UART_TxFloatNumber(var_uartChannel_u8,var_floatNum_f32);
				#endif
				break;



				case 'S':
				case 's': /* Argument type is of string, hence get the pointer to sting passed */
				str = va_arg(argp, uint8 *);
				UART_TxString(var_uartChannel_u8,str);
				break;



				case '%':
				UART_TxChar(var_uartChannel_u8,'%');
				break;
			}
		}
		else
		{
			/* As '%' is not detected transmit the char passed */
			UART_TxChar(var_uartChannel_u8,ch);
		}
	}

	va_end(argp);
}
#endif