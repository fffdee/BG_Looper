/*****************************************************
 mmmmmm                           mmmm     mmmm   
 ##""""##                       ##""""#   ##""##   
 ##    ##   m#####m  ##m####m  ##        ##    ## 
 #######    " mmm##  ##"   ##  ##  mmmm  ##    ## 
 ##    ##  m##"""##  ##    ##  ##  ""##  ##    ## 
 ##mmmm##  ##mmm###  ##    ##   ##mmm##   ##mm##  
 """""""    """" ""  ""    ""     """"     """"   
******************************************************
  funstion: Main component of sequencer
	author  : BanGO
******************************************************/


#include "sequencer.h"
#include "sound.h"
#include "tim.h"
#include "factory.h"
#include "sequencer_source.h"
#include "sound.h"
#include "chord.h"
#include "fingerstyle_tech_func.h"
#include "seq_conf.h"


Task_Run_t task_run = {0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,78.0,mode_Setting};

//const sequencer_rhythm_source_info_t  *sequencer_rhythm =  rhythm_Source[];

//const sequencer_rhythm_source_info_t  *sequencer_second_seq = sequencer_rhythm_second_seq;



void Auto_mode(void)
{
		if(task_run.chord_index<7)task_run.rhythm_index=0;
		if(task_run.chord_index>6)task_run.rhythm_index=1;
		
	  task_run.total = rhythm_Source[task_run.current_tone].main_source[task_run.rhythm_index].total;
		sequencer_rhythm_source_t *source;
	  source = (sequencer_rhythm_source_t *)rhythm_Source[task_run.current_tone].main_source[task_run.rhythm_index].source;
	
		task_run.second_seq_total = rhythm_Source[task_run.current_tone].second_source[task_run.rhythm2_index].total;
		sequencer_rhythm_source_t *second_seq;
		second_seq = (sequencer_rhythm_source_t *)rhythm_Source[task_run.current_tone].second_source[task_run.rhythm2_index].source;
		
	  
  
  if(task_run.sequencer_state){
	
	}
	//	task_run.over_index = task_run.total;
   /* for (uint16_t i = task_run.note_index; i <task_run.over_index; i++)*/
		for (uint16_t i = 0; i <task_run.total; i++){
  
			if (((uint16_t)(source[i].note_on_timestamp) == task_run.sequencer_run_timer)/* && (source[i].note != OVER_SIGN)*/) {
				
					if(source[i].CH<6){
						
							if(source[i].CH==STRING_LOW){
								
								
								Send_MIDI_Data_RAW(0x80|source[i].CH, chord[major[task_run.key_index][task_run.chord_index]][chord[major[task_run.key_index][task_run.chord_index]][6]], source[i].velocity);
								Send_MIDI_Data_RAW(0x90|source[i].CH, chord[major[task_run.key_index][task_run.chord_index]][chord[major[task_run.key_index][task_run.chord_index]][6]], source[i].velocity);
							
							}
							else{
								
								Send_MIDI_Data_RAW(0x80|source[i].CH, chord[major[task_run.key_index][task_run.chord_index]][source[i].CH], source[i].velocity);
								Send_MIDI_Data_RAW(0x90|source[i].CH, chord[major[task_run.key_index][task_run.chord_index]][source[i].CH], source[i].velocity);
							}
							
					}else  if(source[i].CH>5){
								
							//	if(task_run.chord_index>7)	task_run.chord_index = task_run.chord_index-7;
								tech_handle(source[i].CH,task_run.key_index,task_run.chord_index-7,source[i].velocity);
						
					}
	
					
       }
		

				
				
				
        uint16_t note_off_timestamp = source[i].note_off_timestamp;
        
				switch (source[i].note_off_timestamp) { 
        case 251:                               
            note_off_timestamp = source[i].note_off_timestamp * 2;
            break;
         case 255: 
            note_off_timestamp = source[i].note_off_timestamp * 4;
            break;
        default:
            break;
        }
	
				
        note_off_timestamp += source[i].note_on_timestamp;
				if(source[i].CH<5){
				  if ((note_off_timestamp == task_run.sequencer_run_timer)/* && (source[i].note != OVER_SIGN)*/) {
							//Send_MIDI_Data_RAW(0x80|source[i].CH, chord[major[task_run.key_index][task_run.chord_index]][source[i].CH], source[i].velocity);
					}
				}
				
		
				if(task_run.stop_flag ==1){
							
                sequencer_stop();
					task_run.stop_flag  = 0;
				}
				
    }
		

	if(task_run.second_seq_on_off==1){	
		
	for (uint16_t i = 0; i <task_run.second_seq_total; i++){
  
			if (((uint16_t)(second_seq[i].note_on_timestamp) == task_run.sequencer_run_timer)/* && (source[i].note != OVER_SIGN)*/) {
				
					if(second_seq[i].CH<6){
						
							if(second_seq[i].CH==STRING_LOW){
								
								Send_MIDI_Data_RAW(0xAC, second_seq[i].CH, 0x00);
								if(task_run.chord_index>6){
									Send_MIDI_Data_RAW(0x88, chord[major[task_run.key_index][task_run.chord_index-7]][chord[major[task_run.key_index][task_run.chord_index-7]][6]], second_seq[i].velocity);
									Send_MIDI_Data_RAW(0x98, chord[major[task_run.key_index][task_run.chord_index-7]][chord[major[task_run.key_index][task_run.chord_index-7]][6]], second_seq[i].velocity);
								}else{
								
									Send_MIDI_Data_RAW(0x88, chord[major[task_run.key_index][task_run.chord_index]][chord[major[task_run.key_index][task_run.chord_index]][6]], second_seq[i].velocity);
									Send_MIDI_Data_RAW(0x98, chord[major[task_run.key_index][task_run.chord_index]][chord[major[task_run.key_index][task_run.chord_index]][6]], second_seq[i].velocity);
								}
							
							}
							else{
								Send_MIDI_Data_RAW(0xAC, second_seq[i].CH, 0x00);
								
								Send_MIDI_Data_RAW(0x88, chord[major[task_run.key_index][task_run.chord_index]][second_seq[i].CH], second_seq[i].velocity);
								Send_MIDI_Data_RAW(0x98, chord[major[task_run.key_index][task_run.chord_index]][second_seq[i].CH], second_seq[i].velocity);
							}
							
					}else  if(second_seq[i].CH>5){
								
							//	if(task_run.chord_index>7)	task_run.chord_index = task_run.chord_index-7;
								tech_handle(second_seq[i].CH,task_run.key_index,task_run.chord_index-7,second_seq[i].velocity);
						
					}
					if(second_seq[i].CH == OVER_SIGN){
											
												
					}	
					
       }
		 
			uint16_t note_off_timestamp2 = second_seq[i].note_off_timestamp;
						switch (second_seq[i].note_off_timestamp) { 
        case 251:                              
            note_off_timestamp2 = second_seq[i].note_off_timestamp * 2;
            break;
         case 255:
            note_off_timestamp2 = second_seq[i].note_off_timestamp * 4;
            break;
        default:
            break;
        }
  
				note_off_timestamp2 += second_seq[i].note_on_timestamp;
				if(second_seq[i].CH<5){
				  if ((note_off_timestamp2 == task_run.sequencer_run_timer)/* && (source[i].note != OVER_SIGN)*/) {
						//	Send_MIDI_Data_RAW(0x80|source[i].CH, chord[major[task_run.key_index][task_run.chord_index]][source[i].CH], source[i].velocity);
					}
				}
				
				
			}
			
		}

    task_run.sequencer_run_timer++;
}




void Halt_auto_mode(void)
{
		if(task_run.chord_index>6)task_run.rhythm_index=0;
		if(task_run.chord_index<7)task_run.rhythm_index=1;
		sequencer_rhythm_source_t *source;
		task_run.total = rhythm_Source[task_run.current_tone].main_source[task_run.rhythm_index].total-1;
	  
	 // if(task_run.rhythm_index>sequencer_get_tail())task_run.rhythm_index=sequencer_get_tail();
    source = (sequencer_rhythm_source_t *)rhythm_Source[task_run.current_tone].main_source[task_run.rhythm_index].source;
		if(task_run.last_chord!=task_run.chord_index||task_run.last_rhythm!=task_run.rhythm_index){
				
				task_run.bit_count =0;
				task_run.next_bit = 0;
				dream_set_normal_sound();
				for(uint8_t i=0;i<7;i++)
							Send_MIDI_Data_RAW(0xB0|i, 0x78, 0x00);
				
		}
		

		if(task_run.bit_count>task_run.total)task_run.bit_count=0;
		
		task_run.last_chord = task_run.chord_index;
		
		task_run.last_rhythm = task_run.rhythm_index;
		
		if(task_run.bit_count<=task_run.total){
			
					task_run.next_bit = source[task_run.bit_count+1].note_on_timestamp;
					
					if(source[task_run.bit_count].CH<6){
						
						//if(task_run.bit_count>task_run.total)task_run.bit_count=0;
						
						if(source[task_run.bit_count].CH==STRING_LOW){
							
							Send_MIDI_Data_RAW(0x80|source[task_run.bit_count].CH, chord[major[task_run.key_index][task_run.chord_index]][chord[major[task_run.key_index][task_run.chord_index]][6]], source[task_run.bit_count].velocity);
							Send_MIDI_Data_RAW(0x90|source[task_run.bit_count].CH, chord[major[task_run.key_index][task_run.chord_index]][chord[major[task_run.key_index][task_run.chord_index]][6]], source[task_run.bit_count].velocity);
						
						}else{
							if(task_run.bit_count>task_run.total)task_run.bit_count=0;
							Send_MIDI_Data_RAW(0x80|source[task_run.bit_count].CH, chord[major[task_run.key_index][task_run.chord_index]][source[task_run.bit_count].CH], source[task_run.bit_count].velocity);						
							Send_MIDI_Data_RAW(0x90|source[task_run.bit_count].CH, chord[major[task_run.key_index][task_run.chord_index]][source[task_run.bit_count].CH], source[task_run.bit_count].velocity);
							
						}
						
						
					}else{
							//if(task_run.bit_count>task_run.total)task_run.bit_count=0;
							if(source[task_run.bit_count].CH==NoteOffAll) task_run.bit_count++;
							tech_handle(source[task_run.bit_count].CH,task_run.key_index,task_run.chord_index-7,source[task_run.bit_count].velocity);
							
					}
					
					if(source[task_run.bit_count].note_on_timestamp!=task_run.next_bit||task_run.bit_count==task_run.total){
							
							
							sequencer_stop();	
							
					} 
							
		 }
		task_run.bit_count++;
		
			
			
}


void Ble_mode()
{
	
	
	
		
}



Mode_Setting_t mode_Setting[] = {

			{0,Auto_mode},
			{1,Halt_auto_mode},
			{2,Ble_mode},
	
			
};


