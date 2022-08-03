/*
 * Apl_mainControlTsk.c
 *
 * Created: 7/30/2022 7:08:01 AM
 *  Author: ThoPH
 */ 

#include <Apl_mainControlTsk.h>
#include "Apl_MainTskIdle.h"
#include <Apl_uartFFSend.h>

static const MainSts Apl_stateMachine[2][9] = 
{
	{
		&Apl_mainIdle_EvReqWrite,
	    NULL,
		&Apl_mainIdle_EvReqErase,
		NULL,
		&Apl_mainIdle_EvReqVerify,
		NULL,
		&Apl_mainIdle_EvJob,
		&Apl_mainIdle_entry,
		&Apl_mainIdle_exit
	},
	{
		NULL,
		&Apl_mainWriteWait_EvEndWrite,
		NULL,
		NULL,
		NULL,
		NULL,
		&Apl_mainWriteWait_EvJob,
		&Apl_mainWriteWait_entry,
		&Apl_mainWriteWait_exit
	}
};


void Apl_gpioChangeState(uint16 currenstate)
{
	uint16 u2a_currentState;
	
	u2a_currentState = currenstate;
	
	if (STATE_MAXNUMBER <= currenstate) {
		Apl_stateMachine[currenstate][8](u2a_currentState);
	}
	
	
	if (2 < u2a_currentState) {
		u2a_currentState = APL_TASKLISTIDLE;
	}
	
	Apl_gpioCurrentSts = u2a_currentState;
	
	if (NULL != Apl_stateMachine[u2a_currentState][7]) {
		Apl_stateMachine[u2a_currentState][7](currenstate);
	}
}

void Apl_setEvt(uint8 currentSts) {
	if (NULL != Apl_stateMachine[currentSts][7]) {
		Apl_stateMachine[currentSts][7](currentSts);
	}
}

uint16 Apl_getCurrentSts(void)
{
	return Apl_gpioCurrentSts;
}