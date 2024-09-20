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
#include "bg_looper_source.h"

#include <stdio.h>
ErrorCode bg_looper_recording(uint8_t ch);
ErrorCode bg_looper_plays(uint8_t ch);
ErrorCode bg_looper_recording_stop(uint8_t ch);
ErrorCode bg_looper_playing_stop(uint8_t ch);
uint8_t get_loop_source_tone(uint8_t ch);
uint8_t get_loop_source_bgm(uint8_t ch);
uint16_t get_loop_source_total(uint8_t ch);
Note_data get_loop_source_loop_note(uint8_t ch,uint16_t count);

Loop_run_data loop_run_data = {
	
	.looper_enable = 1,
	.record_ch  = INVALID,
	.first_bit = 0,
	.recording_flag = 0,
	.channel_state = {0},
	.loop_play_time = {0},
	.last_note = {0},
	.noteon_time = {0},
	.loop_recording_time = 0,

};

Loop_run_task loop_run_task = {

	.play = bg_looper_plays,
	.recording = bg_looper_recording,
	.record_stop = bg_looper_recording_stop,
	.play_stop = bg_looper_playing_stop,
	.get_total = get_loop_source_total,
	.get_bgm = get_loop_source_bgm,
	.get_tone = get_loop_source_tone,
	.get_loop_note = get_loop_source_loop_note,

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
					loop_run_task.record_stop(i);
					printf("channel %d is Record_stop\n",i);
					break;
				case PLAY_STOP:
					loop_run_task.play_stop(i);
					printf("channel %d is Play_stop\n",i);
					break;
				default:
					break;
			}
		}
	}
		
}


ErrorCode bg_looper_recording(uint8_t ch)
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

ErrorCode bg_looper_plays(uint8_t ch)
{
	
		looper_play(ch);
	
	
}

void loop_note_update(uint8_t ch, uint8_t string, uint8_t note, 
uint8_t vel, uint16_t start_time,uint16_t noteon_time )
{
	loop_source[ch].loop_data[loop_run_data.recording_count].string = 	string;
	loop_source[ch].loop_data[loop_run_data.recording_count].note = note;
	loop_source[ch].loop_data[loop_run_data.recording_count].vel = vel;
	loop_source[ch].loop_data[loop_run_data.recording_count].start_time = start_time;
	loop_source[ch].loop_data[loop_run_data.recording_count].NoteOn_Time = noteon_time;

}

void show_data(uint8_t ch)
{
	printf("The recorder count:%d,\n",loop_source[ch].total);
	for(uint16_t i =0; i<loop_source[ch].total ;i++){
			#ifdef DEBUG
					printf("The recorder updata: string:%d,note :%d, vel:%d, start_time:%d, noteon_time:%d\n"
					,loop_source[ch].loop_data[i].string
					,loop_source[ch].loop_data[i].note
					,loop_source[ch].loop_data[i].vel
					,loop_source[ch].loop_data[i].start_time
					,loop_source[ch].loop_data[i].NoteOn_Time);
				#endif
	}
}

ErrorCode bg_looper_playing_stop(uint8_t ch){

	loop_run_data.channel_state[ch] = INVALID;

}

ErrorCode bg_looper_recording_stop(uint8_t ch)
{
			
		loop_run_data.recording_flag = 0;
		loop_source[ch].total = loop_run_data.recording_count;
		#ifdef DEBUG
				printf("The BG_Looper is record %d bit\n",loop_source[ch].total);
		#endif
		show_data(ch);
		loop_run_data.recording_count = 0;
		for (uint8_t i = 0; i < 6; i++)
		{
			loop_run_data.last_note[i].note = 0;
			loop_run_data.last_note[i].noteon_flag = 0;
			loop_run_data.last_note[i].NoteOn_Time = 0;
			loop_run_data.last_note[i].start_time = 0;
			loop_run_data.last_note[i].vel = 0;
			loop_run_data.last_note[i].string = 0;
		}

			
		loop_run_data.channel_state[ch] = INVALID;
	
		

		return SUCCESS;

}


Note_data  get_loop_source_loop_note(uint8_t ch,uint16_t count){

	Note_data note_data;
	note_data.string = loop_source[ch].loop_data[count].string;
	note_data.note = loop_source[ch].loop_data[count].note;
	note_data.vel = loop_source[ch].loop_data[count].vel;
	note_data.start_time = loop_source[ch].loop_data[count].start_time;
	note_data.NoteOn_Time = loop_source[ch].loop_data[count].NoteOn_Time;
	return note_data;
}

uint8_t get_loop_source_tone(uint8_t ch){

	return loop_source[ch].tone;

}

uint8_t get_loop_source_bgm(uint8_t ch){

	return loop_source[ch].bgm;

}

uint16_t get_loop_source_total(uint8_t ch){

	return loop_source[ch].total;

}