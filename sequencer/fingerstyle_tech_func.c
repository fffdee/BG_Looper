/*****************************************************
 mmmmmm                           mmmm     mmmm   
 ##""""##                       ##""""#   ##""##  
 ##    ##   m#####m  ##m####m  ##        ##    ## 
 #######    " mmm##  ##"   ##  ##  mmmm  ##    ## 
 ##    ##  m##"""##  ##    ##  ##  ""##  ##    ## 
 ##mmmm##  ##mmm###  ##    ##   ##mmm##   ##mm##  
 """""""    """" ""  ""    ""     """"     """"   
******************************************************
  funstion: Handle of sequencer
	author  : BanGO
******************************************************/

#include "sequencer.h"
#include "fingerstyle_tech_func.h"
#include "sound.h"

Tech_deal tech_deal[] = {
	
		{ "NoteOffall"  			, NoteOffall},
		{ "Slap"        			, Slap},
		{ "sycopation"  			, sycopation},
		{ "hit"  							, hit},
		{ "Switch"     				, Switch},
		{ "mhit"							, mhit},
		{ "lhit"							, lhit},
		{ "SweepUp_Mute"			, SweepUp_Mute},
		{ "MuteHandle"			  , Mute},
		{ "UnMute"			  	  , UnMute},
		{	"Sweep_down"				,	Sweep_down},
		{	"Sweep_up"					,	Sweep_up},
		{ "ToneChange"			  , ToneChange},
};	

void NoteOffall(uint8_t vel){

			for(uint8_t i=0;i<7;i++)
							Send_MIDI_Data_RAW(0xB0|i, 0x78, 0x00);	
	
}

void Slap(uint8_t vel)
{
		for(uint8_t i=0;i<6;i++)
							Send_MIDI_Data_RAW(0xB0|i, 0x78, 0x00);	
		Send_MIDI_Data_RAW(0xA8, 36+rand()%4, vel);
}

void sycopation(uint8_t vel)
{
		 for(uint8_t i=0;i<6;i++)
							Send_MIDI_Data_RAW(0xB0|i, 0x78, 0x00);	
		 Send_MIDI_Data_RAW(0xA8, 71+rand()%4, vel);
		
		 
}

void hit(uint8_t vel)
{
		  
		  Send_MIDI_Data_RAW(0xA8, 40+rand()%3,vel);
}

void Switch(uint8_t vel)
{
		 Send_MIDI_Data_RAW(0xA8, 49+rand()%12, vel);
}

void mhit(uint8_t vel)
{
		 Send_MIDI_Data_RAW(0xA8, 46+rand()%3, vel);
}

void lhit(uint8_t vel)
{
		 Send_MIDI_Data_RAW(0xA8, 43+rand()%3, vel);
}

void SweepUp_Mute(uint8_t vel)
{
		// Send_MIDI_Data_RAW(0xA9, 41+chord_index*6, vel);
}


void ToneChange(uint8_t vel)
{
		//Send_MIDI_Data_RAW(0xAA, tone_index, 0x00);
}

void Mute(uint8_t vel)
{
	
		dream_set_muffled_sound();
}

void UnMute(uint8_t vel)
{
	
		dream_set_normal_sound();
}

void Sweep_up(uint8_t vel)
{
	
		Send_MIDI_Data_RAW(0xA8, 67+rand()%5, vel);
}


void Sweep_down(uint8_t vel)
{
	
		Send_MIDI_Data_RAW(0xA8, 61+rand()%5, vel);
}

void tech_handle(uint8_t index,uint8_t vel)
{
	
	if(index == 0x12){
		
			tech_deal[5].handle(vel);
	
	}else if(index == 0x13){
			tech_deal[6].handle(vel);
	}else{
			tech_deal[index-6].handle(vel);
	}
		
	
}



