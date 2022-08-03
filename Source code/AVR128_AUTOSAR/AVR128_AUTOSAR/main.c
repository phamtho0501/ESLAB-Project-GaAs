/*
 * AVR128_AUTOSAR.c
 *
 * Created: 7/18/2022 12:21:24 AM
 * Author : ThoPH
 */ 

#include <Apl_TaskListMain.h>
#include <Apl_Init.h>

int main(void) {

	Apl_Init();
	
	while(1) {
		Apl_mainTask();
	}
	
	return 0;
}

