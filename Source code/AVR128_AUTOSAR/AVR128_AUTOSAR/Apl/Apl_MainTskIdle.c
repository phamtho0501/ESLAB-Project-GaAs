/*
 * Apl_MainTskIdle.c
 *
 * Created: 7/30/2022 7:22:04 AM
 *  Author: ThoPH
 */

#include "Apl_MainTskIdle.h"

void Apl_mainIdle_EvReqWrite(uint16 currentState)
{

	return;	
}

void Apl_mainIdle_EvReqErase(uint16 currentState)
{
	return;
}

void Apl_mainIdle_EvReqVerify(uint16 currentState)
{
	return;
}

void Apl_mainIdle_EvJob(uint16 currentState)
{
	return;
}


void Apl_mainIdle_entry(uint16 currentState)
{
	PORTE |= (1<<PE4);
	_delay_ms(1000);
	PORTE &= ~(1<<PE4);
	_delay_ms(1000);
	return;
}

void Apl_mainIdle_exit(uint16 currentState)
{
	return;
}
