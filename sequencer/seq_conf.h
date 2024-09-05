#ifndef __SEQ_CONF_H__
#define __SEQ_CONF_H__

#include "sequencer.h"
#include "seq_setting.h"


/*************************************************Seq_define_Setting***********************************************************/
#define TONE_COUNT 9

#define CAPO_CHORD 

#define M_GUITAR 	 2
#define BASS     	 2
#define E_GUITAR 	 0
#define PIANO    	 0

extern Rhythm_Source rhythm_Source[TONE_COUNT];
extern sequencer_rhythm_source_info_t sequencer_rhythm_bass_paving_seq[6];
/**********************************************用户设置初始化参数配置***********************************************************/

#define OVER_SIGN 0xF0

#define STRING_LOW 0x00
#define STRING_5 0x01
#define STRING_4 0x02
#define STRING_3 0x03
#define STRING_2 0x04
#define STRING_1 0x05


/***************************************************技巧音指令配置*******************************************************************/


#define NoteOffAll 			0x06		//消音
#define Strum_Slap 			0x07		//拍弦
#define SYCOPATION			0x08    //切音
#define HHIT			  		0x09		//打板
#define SWITCH		    	0x0a
#define MHIT						0x12
#define LHIT						0x13
#define Strum_U1mute		0x0d
#define MUTE						0x0e
#define UNMUTE					0x0f


#define SWEEP_D1        0x10
#define SWEEP_U1        0x11

#define BASS_OFF				0x1F

#define HALF						0x2F



#define NORMAL_COUNT    7
#define ONECHORD_COUNT  11





/*********************************************************************************************************************************/
#endif