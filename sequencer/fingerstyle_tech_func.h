#ifndef __FINGERSTYLE_TECH_FUNC_H__
#define __FINGERSTYLE_TECH_FUNC_H__

#include "stdint.h"

typedef struct{
	
	char * name;
	void (*handle)(uint8_t);

}Tech_deal;


void NoteOffall(uint8_t vel);


void Slap(uint8_t vel);


void sycopation(uint8_t vel);


void hit(uint8_t vel);


void Switch(uint8_t vel);


void mhit(uint8_t vel);


void lhit(uint8_t vel);


void SweepUp_Mute(uint8_t vel);


void ToneChange(uint8_t vel);


void Mute(uint8_t vel);


void UnMute(uint8_t vel);


void Sweep_up(uint8_t vel);



void Sweep_down(uint8_t vel);


void tech_handle(uint8_t index,uint8_t vel);

	


#endif