/*
 * Apl_uartSendFFWait.h
 *
 * Created: 7/30/2022 7:15:27 AM
 *  Author: ThoPH
 */ 


#ifndef APL_UARTSENDFFWAIT_H_
#define APL_UARTSENDFFWAIT_H_

#include <Std_Type.h>

void Apl_mainFFSendWaitExecuteEvjob(uint16 currentState);
void Apl_mainFFSendWaitCompEvjob(uint16 currentState);
void Apl_mainFFSendWaitEntryEvjob(uint16 currentState);
void Apl_mainFFSendWaitTimeOutEvjob(uint16 currentState);


#endif /* APL_UARTSENDFFWAIT_H_ */