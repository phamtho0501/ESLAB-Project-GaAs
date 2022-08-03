/*
 * Public_Variable.h
 *
 * Created: 7/29/2022 11:22:06 PM
 *  Author: ThoPH
 */ 


#ifndef PUBLIC_VARIABLE_H_
#define PUBLIC_VARIABLE_H_

#include <Std_Type.h>
#include <user_config.h>

#define STATE_MAXNUMBER				3u

#define APL_TASKLISTIDLE			0u
#define APL_TASKLISTFFSEND			1u
#define APL_TASKLISTFFWAIT			2u

#define APL_EXECUTE_EVENT_JOB		0u
#define APL_EXECUTE_COMP_JOB		1u
#define APL_EXECUTE_ENTRY_JOB		2u
#define APL_EXECUTE_TIMEOUT_JOB		2u

const uint8 Apl_BufferRead[MAX_BLOCK_READ];
const uint8 Apl_BufferWrite[MAX_BLOCK_WRITE];

uint8 Apl_gpioCurrentSts;

#endif /* PUBLIC_VARIABLE_H_ */