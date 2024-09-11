/*****************************************************
 mmmmmm                           mmmm     mmmm   
 ##""""##                       ##""""#   ##""##   
 ##    ##   m#####m  ##m####m  ##        ##    ## 
 #######    " mmm##  ##"   ##  ##  mmmm  ##    ## 
 ##    ##  m##"""##  ##    ##  ##  ""##  ##    ## 
 ##mmmm##  ##mmm###  ##    ##   ##mmm##   ##mm##  
 """""""    """" ""  ""    ""     """"     """"   
******************************************************
  funstion: Main component of BG_Looper
	author  : BanGO
******************************************************/
#include "bg_looper_setting.h"
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
void bg_looper_note_recorder(uint8_t state, uint8_t note, uint8_t vel);
void bg_looper_get_loop_record(uint8_t ch);

extern Loop_run_data loop_run_data;

BG_Looper bg_looper = {
		
		.enable 	= bg_looper_enable,
		.note_recorder= bg_looper_note_recorder,
		.record 	= bg_looper_record,
		.play     	= bg_looper_play,
		.stop_record  = bg_looper_record_stop,
		.stop_play  = bg_looper_play_stop,
		.state  	= bg_looper_get_state,
		.stop_all 	= bg_looper_stop_all,
		.callback	= bg_looper_callback,
		.get_recording_state = bg_looper_get_recording_state,
		.get_loop_record = bg_looper_get_loop_record,

	
};
void bg_looper_get_loop_record(uint8_t ch){

    show_data(ch);
}

uint8_t bg_looper_get_recording_state (void)
{
	#ifdef DEBUG
		printf("The BG_Looper record state is %d\n",loop_run_data.recording_flag);
	#endif
	return loop_run_data.recording_flag;
}

//To set the callback funstion in the timer callback funstion
void bg_looper_callback(void){

		bg_looper_run();
}

//Get the looper run state
uint8_t bg_looper_get_state(void)
{
	#ifdef DEBUG
		printf("The BG_Looper state is %d\n",loop_run_data.looper_enable);
	#endif
	return loop_run_data.looper_enable;
}


//The funtion of recording note
void bg_looper_note_recorder(uint8_t state, uint8_t note, uint8_t vel) 
{
	uint8_t note_state;
	uint8_t string;
	if(loop_run_data.recording_flag){
		
		note_state = (state>>4)&0x0F;
		string = state&0x0F;
		#ifdef DEBUG
			printf("string %d is noteon %d\n",string,note_state);
		#endif
		if(note_state == 0x9){
			if(loop_run_data.first_bit){
				loop_run_data.last_note[string].start_time = 0;
				
			}
			else
				loop_run_data.last_note[string].start_time = loop_run_data.loop_recording_time;
			
			loop_run_data.last_note[string].vel = vel;
			loop_run_data.last_note[string].note = note;
			loop_run_data.last_note[string].string = string;
			loop_run_data.last_note[string].noteon_flag = 1; 
			#ifdef DEBUG
				printf("The BG_Looper string %d is noteon %d\n",string,note);
			#endif
			
		}
		else if(note_state == 0x8)
		{
			loop_run_data.last_note[string].noteon_flag = 0; 
			loop_run_data.last_note[string].NoteOn_Time = loop_run_data.noteon_time[string];
		
			if((	 loop_run_data.first_bit==1
				  || loop_run_data.last_note[string].start_time  != 0)
				  && loop_run_data.last_note[string].NoteOn_Time != 0)
			{
				loop_run_data.first_bit = 0;		
				#ifdef DEBUG
					printf("The recorder updata: string:%d,note :%d, vel:%d, start_time:%d, noteon_time:%d\n"
					,string
					,loop_run_data.last_note[string].note
					,loop_run_data.last_note[string].vel
					,loop_run_data.last_note[string].start_time
					,loop_run_data.last_note[string].NoteOn_Time);
				#endif
				loop_note_update(loop_run_data.record_ch, string
									   ,loop_run_data.last_note[string].note
									   ,loop_run_data.last_note[string].vel
									   ,loop_run_data.last_note[string].start_time
									   ,loop_run_data.last_note[string].NoteOn_Time);
				loop_run_data.recording_count++;

			}
			
		}
		
		

	}

}

ErrorCode bg_looper_enable(uint8_t enable)
{
		if(enable>1)
		return ERROR_INVALID_INPUT;
		
		loop_run_data.looper_enable = enable;
		#ifdef DEBUG
			printf("The BG_Looper state is %d\n",loop_run_data.looper_enable);
		#endif
		return SUCCESS;
}



ErrorCode bg_looper_record(uint8_t ch, uint8_t tone)
{
		if(ch>MAX_CH) return ERROR_OUT_OF_CH_RANGE;
		loop_run_data.record_ch  = ch;
		loop_run_data.channel_state[ch] = RECORDING;
		#ifdef DEBUG
			printf("The BG_Looper record %d channel is start\n",ch);
		#endif
		return SUCCESS;
}

ErrorCode bg_looper_play(uint8_t ch)
{
		
		loop_run_data.channel_state[ch] = PLAY;
		#ifdef DEBUG
			printf("The BG_Looper play %d channel is start\n",ch);
		#endif
		return SUCCESS;
}

ErrorCode bg_looper_record_stop(uint8_t ch)
{
	
	if(ch>MAX_CH) return ERROR_OUT_OF_CH_RANGE;
    loop_run_data.record_ch  = INVALID;
	loop_run_data.channel_state[ch] = RECORDING_STOP;
	bg_looper_get_loop_record(ch);
	#ifdef DEBUG
			printf("The BG_Looper record %d channel is stop\n",ch);
	#endif
	return SUCCESS;

}

ErrorCode bg_looper_play_stop(uint8_t ch)
{
	
	if(ch>MAX_CH) return ERROR_OUT_OF_CH_RANGE;
	
	loop_run_data.channel_state[ch] = PLAY_STOP;
	#ifdef DEBUG
			printf("The BG_Looper play %d channel is stop\n",ch);
	#endif
	return SUCCESS;

}

ErrorCode bg_looper_stop_all(void)
{
		
		for(uint8_t i = 0; i<MAX_CH; i++) loop_run_data.channel_state[i] = 0; 
			
		return SUCCESS;

}
