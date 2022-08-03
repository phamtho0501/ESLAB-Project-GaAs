/*
 * Apl_mainControlTsk.h
 *
 * Created: 7/30/2022 7:07:52 AM
 *  Author: ThoPH
 */ 


#ifndef APL_MAINCONTROLTSK_H_
#define APL_MAINCONTROLTSK_H_

#include <Std_Type.h>
#include "Apl_Public_Variable.h"

typedef void (*MainSts) (uint16 currentState);

void Apl_setEvt(uint8 currentSts);
uint16 Apl_getCurrentSts(void);
void Apl_gpioChangeState(uint16 currenstate);



#endif /* APL_MAINCONTROLTSK_H_ */