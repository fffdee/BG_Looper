#ifndef __SEQ_SETTING_H__
#define __SEQ_SETTING_H__

#include "stdint.h"

#include "seq_conf.h"

void sequence_init(uint8_t sequencer_bpm_flash,uint8_t rhythm_index_flash);

void sequencer_callback();
void sequencer_play(uint8_t index,uint8_t type,uint8_t vel);
void sequencer_stop();

void sequencer_switch(uint8_t vel);

void sequencer_enable(uint8_t enable);
void second_seq_enable(uint8_t enable);
void sequencer_set_bpm(uint8_t new_bpm);

void sequencer_add_bpm();
void sequencer_dec_bpm();
void sequencer_add_key();
void sequencer_dec_key();

void sequencer_set_chord(uint8_t* one_chord);

void sequencer_set_rhythm(uint8_t tone, uint8_t rhythm_index,sequencer_rhythm_source_info_t source);
void sequencer_set_paving(uint8_t rhythm_index, sequencer_rhythm_source_info_t source);

void sequencer_set_key_index(int8_t index);
void sequencer_set_tone_index(uint8_t index);
void sequencer_set_mode_index(uint8_t index);
void sequencer_set_rhythm_index(uint8_t index);
void sequencer_set_rhythm2_index(uint8_t index);

sequencer_rhythm_source_info_t sequencer_get_rhythm(uint8_t tone, uint8_t rhythm_index);

uint8_t second_seq_enable_state(void);
uint8_t sequencer_get_state(void);
uint8_t sequencer_get_bpm(void);
uint8_t sequencer_get_mode_index(void);
uint8_t sequencer_get_current_tone(void);
uint8_t sequencer_get_current_key(void);
uint8_t sequencer_get_rhythm_index(void);
uint8_t sequencer_get_rhythm2_index(void);
uint8_t sequencer_get_rhythm_tail(void);
uint8_t sequencer_get_rhythm2_tail(void);

void sequencer_HAmode_claer(void);




typedef struct{


		
		void (*callback)(void);
		void (*play)(uint8_t,uint8_t,uint8_t);
		void (*stop)(void);
		void (*Switch)(uint8_t);
		void (*enable)(uint8_t);
		void (*second_seq_enable)(uint8_t);
	
		void (*set_bpm)(uint8_t);
		void (*add_bpm)(void);
		void (*dec_bpm)(void);
		void (*add_key)(void);
		void (*dec_key)(void);
		void (*set_chrod)(uint8_t*);
		void (*set_rhythm)(uint8_t, uint8_t, sequencer_rhythm_source_info_t);
		void (*set_paving)(uint8_t, sequencer_rhythm_source_info_t);
		sequencer_rhythm_source_info_t (*get_rhythm)(uint8_t, uint8_t);
	
		void (*set_key_index)(int8_t);
		void (*set_tone_index)(uint8_t);
		void (*set_rhythm_index)(uint8_t);
		void (*set_rhythm2_index)(uint8_t);
	  void (*set_mode_index)(uint8_t);
		
		uint8_t (*get_state)(void);
		uint8_t (*get_second_seq_state)(void);
		uint8_t (*get_mode_index)(void);
		uint8_t (*get_current_tone)(void);
		uint8_t (*get_current_key)(void);
		uint8_t (*get_rhythm_index)(void);
		uint8_t (*get_rhythm2_index)(void);
		uint8_t (*get_bpm)(void);
		uint8_t (*get_rhythm_tail)(void);
		uint8_t (*get_rhythm2_tail)(void);
		
		void (*HAmode_claer)(void);
		
		
}Seq_setting;


extern Seq_setting seq_setting;

#endif