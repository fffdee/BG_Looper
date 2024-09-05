#include "bg_looper_setting.h"
#include "bg_looper_source.h"
#include "bg_looper.h"
#include "bg_looper_conf.h"

ErrorCode bg_looper_start(uint8_t ch);
ErrorCode bg_looper_enable(uint8_t enable);
ErrorCode bg_looper_stop(uint8_t ch);
ErrorCode bg_looper_stop_all(void);
uint8_t bg_looper_get_state(void);
ErrorCode bg_looper_play(uint8_t ch);
void bg_looper_callback(void);
uint8_t bg_looper_get_recording_state(void);

BG_Looper bg_looper = {
		
		.enable 	= bg_looper_enable,
		.start 		= bg_looper_start,
		.stop  		= bg_looper_stop,
		.play     = bg_looper_play,
		.state  	= bg_looper_get_state,
		.stop_all = bg_looper_stop_all,
		.callback = bg_looper_callback,
		.get_recording_state = bg_looper_get_recording_state,
	
};

uint8_t bg_looper_get_recording_state (void)
{
		
	return 0;
}

void bg_looper_callback(void){

		bg_looper_run();
}

uint8_t bg_looper_get_state(void)
{
	
		return 0;
}


ErrorCode bg_looper_enable(uint8_t enable)
{
		if(enable>1)
		return ERROR_INVALID_INPUT;

	
		
		return SUCCESS;
}

ErrorCode bg_looper_play(uint8_t ch)
{
		
		
		return 0;
}

ErrorCode bg_looper_start(uint8_t ch)
{
		
		return 0;
}


ErrorCode bg_looper_stop(uint8_t ch)
{
		
		return 0;
}


ErrorCode bg_looper_stop_all(void)
{
		
		return 0;
}
