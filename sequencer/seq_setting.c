/*****************************************************
 mmmmmm                           mmmm     mmmm   
 ##""""##                       ##""""#   ##""##   
 ##    ##   m#####m  ##m####m  ##        ##    ## 
 #######    " mmm##  ##"   ##  ##  mmmm  ##    ## 
 ##    ##  m##"""##  ##    ##  ##  ""##  ##    ## 
 ##mmmm##  ##mmm###  ##    ##   ##mmm##   ##mm##  
 """""""    """" ""  ""    ""     """"     """"   
******************************************************
  funstion: Setting funstion of sequencer
	author  : BanGO
******************************************************/

#include "sequencer.h"
#include "seq_conf.h"
#include "seq_setting.h"
#include "sound.h"
#include "tim.h"
#include "fingerstyle_tech_func.h"

const float sequencer_bpm_diff = 0.08333; 
const float sequencer_bpm_benchmark = 120.0;


const uint8_t rhythm_tail[TONE_COUNT][2] = {
	
		{M_GUITAR,BASS},
		{PIANO   ,BASS},
		{E_GUITAR,BASS},
		{BASS    ,M_GUITAR},
		{M_GUITAR,BASS},

};

Seq_setting seq_setting = {

		
		sequencer_callback,
		sequencer_play,
		sequencer_stop,
		sequencer_switch,
		sequencer_enable,
		second_seq_enable,
	
		sequencer_set_bpm,
		sequencer_add_bpm,
		sequencer_dec_bpm,
		
		sequencer_add_key,
		sequencer_dec_key,
		
    sequencer_set_chord,
		sequencer_set_rhythm,
		sequencer_set_paving,
		sequencer_get_rhythm,
	
		sequencer_set_key_index,
		sequencer_set_tone_index,
		sequencer_set_rhythm_index,
		sequencer_set_rhythm2_index,
		sequencer_set_mode_index,
	
		sequencer_get_state,
		second_seq_enable_state,
		sequencer_get_mode_index,
		sequencer_get_current_tone,
		sequencer_get_current_key,
		sequencer_get_rhythm_index,
		sequencer_get_rhythm2_index,
		sequencer_get_bpm,
		sequencer_get_rhythm_tail,
		sequencer_get_rhythm2_tail,
			
		sequencer_HAmode_claer,
		

};


void sequencer_callback()
{
    
		mode_Setting[task_run.sequencer_mode].task();
		
    
}

static void  updata_sequencer_bpm(uint16_t sequencer_bpm)
{
    uint16_t tim_period = (float)(sequencer_bpm_benchmark / sequencer_bpm) * 1000;
    __HAL_TIM_SET_AUTORELOAD(&htim5, tim_period - 1);
}



void sequencer_set_bpm(uint8_t new_bpm)
{
		
		if (new_bpm > 240.0 || new_bpm < 40) return;

    task_run.sequencer_bpm = (float)new_bpm;
    updata_sequencer_bpm(task_run.sequencer_bpm);
	
}

void sequencer_enable(uint8_t enable)
{
		task_run.enable = enable;
		
}


void sequencer_play(uint8_t index,uint8_t type,uint8_t vel)
{
	
		if(task_run.sequencer_mode==1&&task_run.one_chord[0]>OVER_SIGN) return;
		task_run.enable = 1;
		task_run.chord_index = index;
		task_run.play_type = type;
		sequencer_rhythm_source_t *source;
		task_run.total = rhythm_Source[task_run.current_tone].main_source[task_run.rhythm_index].total;
	  source = (sequencer_rhythm_source_t *)rhythm_Source[task_run.current_tone].main_source[task_run.rhythm_index].source;

		task_run.vel = vel;
	
			
		if(task_run.first_flag)
			for(uint8_t i=0;i<7;i++)
							Send_MIDI_Data_RAW(0xB0|i, 0x78, 0x00);	
	
	
		if(task_run.halt_mode==1){
			
				task_run.half_flag = !task_run.half_flag;
			
			
			if(task_run.half_flag&&(task_run.last_chord==task_run.chord_index)){
						
					
					
						task_run.sequencer_run_timer = source[task_run.half_count].note_on_timestamp;
				
					}else{
					 task_run.half_flag = 0;
					 task_run.sequencer_run_timer = 0;
					}

			 }else {

					 task_run.sequencer_run_timer = 0;
			 }
	
    if (task_run.sequencer_state == 0) { 
        task_run.sequencer_state = 1;
			
			
       updata_sequencer_bpm(task_run.sequencer_bpm);
		
    } else {
			
			
     
        sequencer_set_bpm(task_run.sequencer_bpm);
		
    }
 
    HAL_TIM_Base_Start_IT(&htim5);
		task_run.last_chord = index;
}



void sequencer_stop()
{
		task_run.sequencer_state = 0;

    task_run.sequencer_run_timer = 0;
		
		task_run.start = 0;
		
		task_run.start2 = 0;
	
		task_run.over = 0;
	
		task_run.over2 = 0;
	
		task_run.half_flag = 1;
	
		task_run.half_count = 0;
	
		task_run.half_count2 = 0;

	
}


void sequencer_switch(uint8_t vel)
{
		tech_handle(10,vel);
}

void second_seq_enable(uint8_t enable)
{
			task_run.second_seq_on_off = enable;
}



void sequencer_add_bpm()
{
		if (task_run.sequencer_bpm < 240) {
        task_run.sequencer_bpm += 5;
        if (task_run.sequencer_bpm > 240) task_run.sequencer_bpm = 240;
        sequencer_set_bpm(task_run.sequencer_bpm);
    }
}

void sequencer_dec_bpm()
{
		if (task_run.sequencer_bpm > 40) {
        task_run.sequencer_bpm -= 5;
        if (task_run.sequencer_bpm < 40) task_run.sequencer_bpm = 40;
        sequencer_set_bpm(task_run.sequencer_bpm);
    }
}

void sequencer_set_chord(uint8_t* one_chord)
{
	 for(uint8_t i = 0;i<7;i++)
	{
			task_run.one_chord[i] = one_chord[i] ;
	}
}

void sequencer_set_rhythm(uint8_t tone, uint8_t rhythm_index, sequencer_rhythm_source_info_t source)
{
		rhythm_Source[tone].main_source[rhythm_index].rhythm_id = source.rhythm_id;
		rhythm_Source[tone].main_source[rhythm_index].total = source.total;
		rhythm_Source[tone].main_source[rhythm_index].sequencer_bpm = source.sequencer_bpm;
		for(uint8_t i=0;i<source.total;i++){
			rhythm_Source[tone].main_source[rhythm_index].source[i] = source.source[i];
		}
	
}

void sequencer_set_paving(uint8_t rhythm_index, sequencer_rhythm_source_info_t source)
{
		sequencer_rhythm_bass_paving_seq[rhythm_index].rhythm_id = source.rhythm_id ;
		sequencer_rhythm_bass_paving_seq[rhythm_index].total = source.total;
		sequencer_rhythm_bass_paving_seq[rhythm_index].sequencer_bpm = source.sequencer_bpm;
		for(uint8_t i=0;i<source.total;i++){
			sequencer_rhythm_bass_paving_seq[rhythm_index].source[i] = source.source[i];
		}
}



sequencer_rhythm_source_info_t sequencer_get_rhythm(uint8_t tone, uint8_t rhythm_index)
{
	 
		return rhythm_Source[tone].main_source[rhythm_index];
}



void sequencer_set_key_index(int8_t index){
		
		task_run.key_index = index;

}	

void sequencer_add_key()
{
		#ifdef CAPO_CHORD	
		task_run.key_index+=1;
		if(task_run.key_index>12)task_run.key_index=12;
		#else 
		task_run.key_index+=1;
		if(task_run.key_index>11)task_run.key_index=11;
		#endif
}

void sequencer_dec_key()
{
		if(task_run.key_index==-6) return;
		task_run.key_index-=1;
		
}


void sequencer_set_tone_index(uint8_t index)
{
		task_run.current_tone = index;
}

void sequencer_set_mode_index(uint8_t index)
{
		task_run.sequencer_mode = index;
}


void sequencer_set_rhythm_index(uint8_t index)
{
		if(index<=sequencer_get_rhythm_tail())
		task_run.rhythm_index = index;
}

void sequencer_set_rhythm2_index(uint8_t index)
{
		if(index<=sequencer_get_rhythm2_tail())
		task_run.rhythm2_index = index;
}

uint8_t sequencer_get_state(void)
{
		return  task_run.enable;
}

uint8_t sequencer_get_bpm(void)
{
		 return (uint8_t)task_run.sequencer_bpm;
}

uint8_t sequencer_get_mode_index(void)
{
		return task_run.sequencer_mode;
}

uint8_t sequencer_get_current_tone(void)
{
		return task_run.current_tone;
}

uint8_t sequencer_get_current_key(void)
{
		return task_run.key_index;
}

uint8_t sequencer_get_rhythm_index(void)
{
		return task_run.rhythm_index;
}

uint8_t sequencer_get_rhythm2_index(void)
{
		return task_run.rhythm2_index;
}

uint8_t sequencer_get_rhythm_tail(void)
{
		return rhythm_tail[task_run.current_tone][0];
}

uint8_t second_seq_enable_state(void)
{
		return task_run.second_seq_on_off;
}


uint8_t sequencer_get_rhythm2_tail(void)
{
		return 6;
}

void sequencer_HAmode_claer(void)
{
		task_run.bit_count = 0;
		task_run.next_bit = 0;
	
}

void sequence_init(uint8_t sequencer_bpm_flash,uint8_t rhythm_index_flash)
{
    task_run.sequencer_bpm = (float)sequencer_bpm_flash;
		task_run.rhythm_index = rhythm_index_flash;
    
}







