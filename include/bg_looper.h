#ifndef _BG_LOOPER_H_
#define _BG_LOOPER_H_

#include "stdint.h"
#include "bg_looper_conf.h"


typedef struct{
	
	uint8_t vel;
	uint8_t note;
	uint8_t string;
	uint8_t noteon_flag;
	uint16_t start_time;
	uint16_t NoteOn_Time;

}Last_note;

typedef struct{
	
	uint8_t looper_enable;
	uint8_t record_ch; 
	uint8_t first_bit;
	uint8_t recording_flag;
	uint8_t play_flag[MAX_CH];
	uint8_t channel_state[MAX_CH];
	Last_note last_note[6];
	uint16_t noteon_time[6];
	uint16_t loop_play_time[MAX_CH];
	uint16_t recording_count;
	uint16_t loop_recording_time;

}Loop_run_data;

typedef struct{
	
		ErrorCode (*recording)(uint8_t);
		ErrorCode (*play)(uint8_t);
		ErrorCode (*stop)(uint8_t, uint8_t);

}Loop_run_task;

void show_data(uint8_t ch);
void loop_note_update(uint8_t ch, uint8_t string, uint8_t note, 
uint8_t vel, uint16_t start_time,uint16_t noteon_time );
void bg_looper_run(void);

#endif