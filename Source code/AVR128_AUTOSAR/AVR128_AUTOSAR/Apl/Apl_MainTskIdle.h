/*
 * Apl_MainTskIdle.h
 *
 * Created: 7/30/2022 7:21:47 AM
 *  Author: ThoPH
 */ 


#ifndef APL_MAINTSKIDLE_H_
#define APL_MAINTSKIDLE_H_

#include <Apl_mainControlTsk.h>
#include <Std_Type.h>
#include <Bsw.h>

void Apl_mainIdle_EvReqWrite(uint16 currentState);
void Apl_mainIdle_EvReqErase(uint16 currentState);
void Apl_mainIdle_EvReqVerify(uint16 currentState);
void Apl_mainIdle_EvJob(uint16 currentState);
void Apl_mainIdle_entry(uint16 currentState);
void Apl_mainIdle_exit(uint16 currentState);



#endif /* APL_MAINTSKIDLE_H_ */