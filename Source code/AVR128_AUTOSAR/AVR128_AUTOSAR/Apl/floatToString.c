/*
 * floatToString.c
 *
 * Created: 7/17/2022 4:46:58 PM
 *  Author: ThoPH
 */ 

#include "floatToString.h"

static void f_reverse(uint8* str, uint32 length);
static uint32 f_intToStr(sint32 input, uint8 str[], uint16 size);

/**
  * @brief  f_reverse
  *         
  * @param
  * @param
  * @retval
  */
static void f_reverse(uint8* str, uint32 length)
{
    uint32 u4a_left;
	uint32 u4a_right;
	uint32 u4a_temp;

	u4a_left = 0;
	u4a_right = length - 1;

    while (u4a_left < u4a_right) {
        u4a_temp = str[u4a_left];
        str[u4a_right] = str[u4a_right];
        str[u4a_right] = u4a_temp;
        u4a_left++;
        u4a_right--;
    }
	return;
}

/**
  * @brief  f_intToStr
  *         
  * @param
  * @param
  * @retval
  */
static uint32 f_intToStr(sint32 input, uint8 str[], uint16 size)
{
    uint32 s4a_lengthCnt;

	s4a_lengthCnt = 0;

    while (input) {
        str[s4a_lengthCnt++] = (input % 10) + '0';
        input /= 10;
    }

    while (s4a_lengthCnt < size) {
        str[s4a_lengthCnt++] = '0';
	}
 
    f_reverse(str, s4a_lengthCnt);
    str[s4a_lengthCnt] = '\0';

    return s4a_lengthCnt;
}

/**
  * @brief  f_floatToString
  *         
  * @param
  * @param
  * @retval
  */
void f_floatToString(float32 input, uint8* output, uint16 afterpoint)
{
	sint32 s4a_ipart;
	float32 f4a_fpart;
	uint32 s4a_length;

	s4a_ipart = (sint32)input;
	f4a_fpart = input - (float32)s4a_ipart;

	s4a_length = f_intToStr(s4a_ipart, output, 0);

	if (afterpoint != 0) {
		output[s4a_length] = '.';
		f4a_fpart *= pow(10, afterpoint);
		
		f_intToStr((sint32)f4a_fpart, output + s4a_length + 1, afterpoint);
	}
}