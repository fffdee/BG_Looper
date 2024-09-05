#include "bg_looper_setting.h"
#include "bg_looper_source.h"
#include "bg_looper.h"
#include "bg_looper_conf.h"
#include <stdio.h>

ErrorCode bg_looper_play(uint8_t ch);
ErrorCode bg_looper_record(uint8_t ch, uint8_t tone);
ErrorCode bg_looper_enable(uint8_t enable);
ErrorCode bg_looper_play_stop(uint8_t ch);
ErrorCode bg_looper_record_stop(uint8_t ch);
ErrorCode bg_looper_stop_all(void);
uint8_t bg_looper_get_state(void);
void bg_looper_callback(void);
uint8_t bg_looper_get_recording_state(void);

extern Loop_run_data loop_run_data;

BG_Looper bg_looper = {
		
		.enable 	= bg_looper_enable,
		.record 	= bg_looper_record,
		.play     	= bg_looper_play,
		.stop_record  = bg_looper_record_stop,
		.stop_play  = bg_looper_play_stop,
		.state  	= bg_looper_get_state,
		.stop_all 	= bg_looper_stop_all,
		.callback	= bg_looper_callback,
		.get_recording_state = bg_looper_get_recording_state,
	
};

uint8_t bg_looper_get_recording_state (void)
{
	return loop_run_data.recording_flag;
}

void bg_looper_callback(void){

		bg_looper_run();
}

uint8_t bg_looper_get_state(void)
{
	return loop_run_data.looper_enable;
}

void note_recorder(uint8_t state, uint8_t note, uint8_t vel) 
{
	uint8_t note_state;
	uint8_t string;
	if(loop_run_data.recording_flag){
		
		note_state = (state>>4)&0x0F;
		string = state&0x0F;

		if(note_state == 0x90){
			// if
			// loop_run_data.last_note[string].start_time;
		}
		else if(note_state == 0x80)
		{

		}


	}

}

ErrorCode bg_looper_enable(uint8_t enable)
{
		if(enable>1)
		return ERROR_INVALID_INPUT;

		loop_run_data.looper_enable = enable;
		
		return SUCCESS;
}



ErrorCode bg_looper_record(uint8_t ch, uint8_t tone)
{
		if(ch>MAX_CH) return ERROR_OUT_OF_CH_RANGE;

		loop_run_data.channel_state[ch] = 1;

		return SUCCESS;
}

ErrorCode bg_looper_play(uint8_t ch)
{
		
		loop_run_data.channel_state[ch] = 2;
		
		return SUCCESS;
}

ErrorCode bg_looper_record_stop(uint8_t ch)
{
	
	if(ch>MAX_CH) return ERROR_OUT_OF_CH_RANGE;
	
	loop_run_data.channel_state[ch] = 3;
	
	return SUCCESS;

}

ErrorCode bg_looper_play_stop(uint8_t ch)
{
	
	if(ch>MAX_CH) return ERROR_OUT_OF_CH_RANGE;
	
	loop_run_data.channel_state[ch] = 4;
	
	return SUCCESS;

}

ErrorCode bg_looper_stop_all(void)
{
		
		for(uint8_t i = 0; i<MAX_CH; i++) loop_run_data.channel_state[i] = 0; 
			
		return SUCCESS;

}
