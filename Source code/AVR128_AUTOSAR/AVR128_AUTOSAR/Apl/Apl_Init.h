/*
 * Apl_Init.h
 *
 * Created: 7/29/2022 11:50:46 PM
 *  Author: ThoPH
 */ 


#ifndef APL_INIT_H_
#define APL_INIT_H_

#include <Bsw.h>
#include "Apl_Public_Variable.h"
#include "Apl_mainControlTsk.h"

void Apl_Init(void);
void Apl_networkInit(void);
void Apl_mainTaskStateInit(void);

#endif /* APL_INIT_H_ */