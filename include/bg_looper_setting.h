#ifndef _BG_LOOPER_SETTING_H_
#define _BG_LOOPER_SETTING_H_

#include "stdint.h"
#include "bg_looper_conf.h"

typedef struct{

		ErrorCode (*enable)(uint8_t);
		void (*note_recorder)(uint8_t,uint8_t,uint8_t);
		ErrorCode (*record)(uint8_t,uint8_t);
		ErrorCode (*play)(uint8_t);
		ErrorCode (*stop_record)(uint8_t);
		ErrorCode (*stop_play)(uint8_t);
		ErrorCode (*stop_all)(void);
		uint8_t (*state)(void);
		void (*callback)(void);
		uint8_t (*get_recording_state)(void);
		void (*get_loop_record)(uint8_t);

}BG_Looper;


extern BG_Looper bg_looper;

#endif