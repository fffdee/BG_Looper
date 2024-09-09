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
#include "bg_looper.h"
#include "bg_looper_conf.h"
#include "bg_looper_setting.h"
#include "bg_looper_play.h"
#include <stdio.h>

uint8_t bg_looper_recording(uint8_t ch);
uint8_t bg_looper_plays(uint8_t ch);
uint8_t bg_looper_stop(uint8_t state ,uint8_t ch);
Loop_run_data loop_run_data = {
	
	.looper_enable = 1,
	.first_bit = 0,
	.recording_flag = 0,
	.channel_state = {3},
	.loop_play_time = {0},
	.last_note = {0},
	.noteon_time = {0},
	.loop_recording_time = 0,
	
	

};

Loop_run_task loop_run_task = {

	.play = bg_looper_plays,
	.recording = bg_looper_recording,
	.stop = bg_looper_stop,

};
//每1毫秒调用这个函数一次
void bg_looper_run(void)
{
	if(loop_run_data.looper_enable){
		for(uint8_t i=0;i<MAX_CH;i++){
			
			
			switch (loop_run_data.channel_state[i])
			{
				case RECORDING:
					loop_run_task.recording(i);
					break;

				case PLAY:
					loop_run_task.play(i);
					break;
				
				case RECORDING_STOP:
					loop_run_task.stop(RECORDING_STOP,i);
					printf("channel %d is Record_stop\n",i);
					break;
				case PLAY_STOP:
					loop_run_task.stop(PLAY_STOP,i);
					printf("channel %d is Play_stop\n",i);
					break;
				default:
					break;
			}
		}
	}
		
}


uint8_t bg_looper_recording(uint8_t ch)
{
	if(loop_run_data.recording_flag!=1){
		loop_run_data.first_bit = 1;
		loop_run_data.recording_flag = 1;
	}else {
		
		loop_run_data.loop_recording_time++;
		for (uint8_t i = 0; i < 6; i++)
		{
			if(loop_run_data.last_note[i].noteon_flag == 1)
				loop_run_data.noteon_time[i]++;
			else
				loop_run_data.noteon_time[i]=0;
		}
		
	}
	
	
}

uint8_t bg_looper_plays(uint8_t ch)
{
	
		looper_play(ch);
	
	
}

uint8_t bg_looper_stop(uint8_t state, uint8_t ch)
{
		if(state){

		 looper_stop(ch);

		}else loop_run_data.recording_flag = 0;

		loop_run_data.channel_state[ch] = INVALID;

}