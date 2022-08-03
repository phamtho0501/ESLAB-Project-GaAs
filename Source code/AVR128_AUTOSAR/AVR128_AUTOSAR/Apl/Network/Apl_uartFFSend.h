/*
 * Apl_uartFFSend.h
 *
 * Created: 7/30/2022 7:13:37 AM
 *  Author: ThoPH
 */ 


#ifndef APL_UARTFFSEND_H_
#define APL_UARTFFSEND_H_

#include <Std_Type.h>

void Apl_mainWriteWait_EvEndWrite(uint16 currentState);
void Apl_mainWriteWait_EvJob(uint16 currentState);
void Apl_mainWriteWait_entry(uint16 currentState);
void Apl_mainWriteWait_exit(uint16 currentState);



#endif /* APL_UARTFFSEND_H_ */