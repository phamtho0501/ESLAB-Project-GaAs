/*
 * Apl_Init.c
 *
 * Created: 7/29/2022 11:51:01 PM
 *  Author: ThoPH
 */

#include <Apl_Init.h>
#include "string.h"
#include "Apl_Public_Variable.h"


void Apl_mainTaskStateInit(void)
{
	Apl_gpioCurrentSts = APL_TASKLISTIDLE;
	Apl_setEvt(Apl_gpioCurrentSts);
	
	return;
}

void Apl_networkInit(void)
{
	memset((void*)Apl_BufferRead, ZERO, sizeof(Apl_BufferRead));
	memset((void*)Apl_BufferWrite, ZERO, sizeof(Apl_BufferWrite));
	return;	
}

void Apl_Init(void)
{
	BSW_driverInit();
	Apl_networkInit();
	Apl_mainTaskStateInit();
	
	return;
}

