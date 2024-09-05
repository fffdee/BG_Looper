#ifndef __SEQUENCER_H__
#define __SEQUENCER_H__

#include "stdint.h"


typedef struct{
		
		uint8_t task_index;
	
		void (*task)(void);
	
}Mode_Setting_t;




typedef struct{

		uint8_t enable;
		uint8_t sequencer_state;				//音序器运行状态
		uint8_t sequencer_mode;					//音序器模式 
		uint8_t current_tone;						//当前音色
		uint8_t rhythm_index;				   	//节奏型切换
		uint8_t rhythm2_index;				   	//节奏型切换
		uint8_t chord_index;						//和弦序号
	  int8_t key_index;							//当前调式
		uint8_t second_seq_on_off;			//铺底开关          
		uint32_t sequencer_run_timer;
		uint8_t halt_mode;
		uint8_t half_flag;
		uint8_t start;
		uint8_t over;
		uint8_t half_count;
		uint8_t start2;
		uint8_t over2;
		uint8_t half_count2;
		uint8_t total;
		uint8_t second_seq_total;
		uint8_t first_flag;
		uint8_t bit_count;
		uint16_t next_bit;
		uint8_t last_chord;
		uint8_t last_rhythm;
		uint8_t vel;
		uint8_t play_type;
		uint8_t one_chord[7];
		uint8_t Switch;
		float sequencer_bpm; 						 //BPM
		Mode_Setting_t *set[3];
		
}Task_Run_t;




extern Task_Run_t task_run;
extern Mode_Setting_t mode_Setting[]; 



typedef struct {
	
  
    uint8_t velocity;
	
		uint8_t CH;
	
	  uint16_t note_on_timestamp;
	
    uint16_t note_off_timestamp;

	
}sequencer_rhythm_source_t;

//typedef struct {
//	
//    uint16_t note_on_timestamp;
//	
//    uint16_t note_off_timestamp;
//		
//    uint8_t velocity;
//	
//		uint8_t CH;

//	
//}sequencer_rhythm_source_t;



typedef struct {
		
		uint8_t	rhythm_id;
		
    uint8_t total;
	
    uint8_t sequencer_bpm;
	
    sequencer_rhythm_source_t *source;
  
}sequencer_rhythm_source_info_t;


typedef struct{
		
	sequencer_rhythm_source_info_t *main_source;
	
	sequencer_rhythm_source_info_t *second_source;
		

}Rhythm_Source;



#endif