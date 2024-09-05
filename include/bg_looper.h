#ifndef _BG_LOOPER_H_
#define _BG_LOOPER_H_

#include "stdint.h"
#include "bg_looper_conf.h"

typedef struct{
	
	uint8_t loop_state;
	uint8_t recording_flag;
	uint8_t channel_state[MAX_CH];
	uint16_t loop_run_time;
	
	
}Loop_run_data;

typedef struct{
	
		ErrorCode (*recording)(uint8_t);
		ErrorCode (*play)(uint8_t);

}Loop_run_task;
void bg_looper_run(void);
extern Loop_run_data loop_run_data;
#endif