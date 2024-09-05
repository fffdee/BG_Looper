#include "bg_looper.h"
#include "bg_looper_conf.h"

Loop_run_data loop_run_data = {
	
	.loop_state = 0,
	.loop_run_time = 0,
	.channel_state = {0},
	

};

Loop_run_task loop_run_task = {

	.play = bg_looper_play,
	.recording = bg_looper_recording,

};
//每1毫秒调用这个函数一次
void bg_looper_run(void)
{
	for(uint8_t i=0;i<MAX_CH;i++){

		switch (loop_run_data.channel_state[i])
		{
			case RECORDING:
				loop_run_task.recording(i);
				break;

			case PLAY:
				loop_run_task.play(i);
				break;

			default:
				break;
		}
	}
		
}


uint8_t bg_looper_recording(uint8_t ch)
{

	
}

uint8_t bg_looper_play(uint8_t ch)
{

}