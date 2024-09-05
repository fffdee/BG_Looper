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
#include "seq_setting.h"
#include "sound.h"
#include "chord.h"
#include "fingerstyle_tech_func.h"
#include "seq_conf.h"



Task_Run_t task_run = {
	
	.enable = 						0,
	.sequencer_state = 		0,						//音序器运行状态
	.sequencer_mode = 		0,						//音序器模式 
	.current_tone = 			0,						//当前音色
	.rhythm_index =				0,				   	//节奏型切换
	.rhythm2_index = 			0,				   	//节奏型切换
	.chord_index = 				0,						//和弦序号
	#ifdef CAPO_CHORD
	.key_index = 					0,						//当前调式
	#else
	.key_index = 					0,	
	#endif
	.second_seq_on_off =  0,						//铺底开关          
	.sequencer_run_timer= 0,
#ifdef ENABLE_USB_LOAD_AUTO_RHYTHM_SOURCE
	.halt_mode = 					1,
#else
	.halt_mode = 					1,
#endif
	.half_flag =          1,
	.start =              0,
	.over = 							0,
	.half_count = 				0,
	.start2 = 						0,
	.over2 = 							0,
	.half_count2 = 				0,
	.total =  						0,
	.second_seq_total =		0,
	.first_flag = 				0,
	.bit_count = 					0,
	.next_bit =						0,
	.last_chord = 				0,
	.last_rhythm = 				0, 	
	.vel = 							 70,
	.play_type = 					0,
	.one_chord= {0xff,0xff,0xff,0xff,0xff,0xff,0},
	.Switch =             0,						//换和弦刮镲声
	.sequencer_bpm = 78.0,						 //BPM
	.set = mode_Setting,
	
};


uint8_t vel_pre_deal(uint8_t vel)
{
	if(task_run.half_count){	
		// if(vel<30)vel = 30;
		
		// if(task_run.vel<50)
		// 	vel = vel-10;
		// if(task_run.vel<70&&task_run.vel>50)
		// 	vel = vel-5;
		// if(task_run.vel<100&&task_run.vel>70)
		// 	vel = vel;
		// if(task_run.vel<127&&task_run.vel>100)
		// 	vel = vel+5;
		vel = (float)task_run.vel / 80.0f  *vel;
		if(vel<20)vel = 20;
		if(task_run.play_type == 0)
		{
			if(vel>115)vel = 115;
		}else
		{
			if(vel>127)vel = 127;
		}
	}
		return vel;
}

void Auto_mode(void)
{
		if(task_run.play_type)task_run.rhythm_index=1;
		else task_run.rhythm_index = 0;
		
		
	
		if(task_run.chord_index>ONECHORD_COUNT) 
			return;
	
	  task_run.total = rhythm_Source[task_run.current_tone].main_source[task_run.rhythm_index].total;
		sequencer_rhythm_source_t *source;
	  source = (sequencer_rhythm_source_t *)rhythm_Source[task_run.current_tone].main_source[task_run.rhythm_index].source;
	
		task_run.second_seq_total = rhythm_Source[task_run.current_tone].second_source[task_run.rhythm2_index].total;
		sequencer_rhythm_source_t *second_seq;
		second_seq = (sequencer_rhythm_source_t *)rhythm_Source[task_run.current_tone].second_source[task_run.rhythm2_index].source;
		
	  if(task_run.enable&&task_run.sequencer_state){
		
		//if(task_run.sequencer_state){
					
				
		//}
//		for (uint8_t i = 0; i < task_run.total; i++)
//	    if(source[i].CH==HALF )task_run.half_count = i;
//		
//		
		if(task_run.halt_mode)
		{
				for (uint8_t i = 0; i < task_run.total; i++)if(source[i].CH==HALF )task_run.half_count = i;
				if(task_run.half_flag&&(task_run.last_chord==task_run.chord_index||task_run.first_flag)){
				
					
					task_run.start = task_run.half_count;
					task_run.over = task_run.total;
				}else{
					task_run.start = 0;
					task_run.over = task_run.half_count;
				
				}
					
		
		}else{
					task_run.start = 0;
					task_run.over = task_run.total;	
		}
	//	task_run.over_index = task_run.total;

		for (uint8_t i = task_run.start; i <task_run.over; i++){
			
			
			if (((uint16_t)(source[i].note_on_timestamp) == task_run.sequencer_run_timer)/* && (source[i].note != OVER_SIGN)*/) {
				
					if(source[i].CH<6){
						
							if(source[i].CH==STRING_LOW){
								
							//	Send_MIDI_Data_RAW(0xa0,0,task_run.vel);
							#ifdef CAPO_CHORD
							
								Send_MIDI_Data_RAW(0x80|source[i].CH, capo_chord[task_run.chord_index][capo_chord[task_run.chord_index][6]]+task_run.key_index , vel_pre_deal(source[i].velocity));
								Send_MIDI_Data_RAW(0x90|source[i].CH, capo_chord[task_run.chord_index][capo_chord[task_run.chord_index][6]]+task_run.key_index, vel_pre_deal(source[i].velocity));
								
								
							#else
								Send_MIDI_Data_RAW(0x80|source[i].CH, chord[major[task_run.key_index][task_run.chord_index]][chord[major[task_run.key_index][task_run.chord_index]][6]], vel_pre_deal(source[i].velocity));
								Send_MIDI_Data_RAW(0x90|source[i].CH, chord[major[task_run.key_index][task_run.chord_index]][chord[major[task_run.key_index][task_run.chord_index]][6]], vel_pre_deal(source[i].velocity));
							#endif
							}
							else{
							//	Send_MIDI_Data_RAW(0xa0,0,task_run.vel);
								#ifdef CAPO_CHORD
							
									Send_MIDI_Data_RAW(0x80|source[i].CH, capo_chord[task_run.chord_index][source[i].CH]+task_run.key_index, vel_pre_deal(source[i].velocity));
									Send_MIDI_Data_RAW(0x90|source[i].CH, capo_chord[task_run.chord_index][source[i].CH]+task_run.key_index, vel_pre_deal(source[i].velocity));
									
								#else
									Send_MIDI_Data_RAW(0x80|source[i].CH, chord[major[task_run.key_index][task_run.chord_index]][source[i].CH], vel_pre_deal(source[i].velocity));
									Send_MIDI_Data_RAW(0x90|source[i].CH, chord[major[task_run.key_index][task_run.chord_index]][source[i].CH], vel_pre_deal(source[i].velocity));
								#endif
							}
							
					}else if(source[i].CH==HALF)
					{
						
								//task_run.half_count = i;
		
								
					}else  if(source[i].CH>5){
								
							//	if(task_run.chord_index>7)	task_run.chord_index = task_run.chord_index-7;
								tech_handle(source[i].CH,vel_pre_deal(source[i].velocity));
						
					}
					
//					if(i== task_run.over-1){
//							
//						//	task_run.sequencer_run_timer = 0;
//							task_run.sequencer_state = 0;
//					
//					}
					
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
				
		

				
    }
		

	if(task_run.second_seq_on_off==1){	
		
		
		
		if(task_run.halt_mode)
		{
				for (uint8_t i = 0; i < task_run.second_seq_total; i++)
				if(second_seq[i].CH==HALF ) task_run.half_count2 = i;
				if(task_run.half_flag){
					
					task_run.start2 = task_run.half_count2;
					task_run.over2 = task_run.second_seq_total;
				}else{
					task_run.start2 = 0;
					task_run.over2 = task_run.half_count2;
				
				}
					
		
		}else{
					task_run.start2 = 0;
					task_run.over2 = task_run.second_seq_total;	
		}
		
		for (uint16_t i = task_run.start2; i <task_run.over2; i++){
  
			if (((uint16_t)(second_seq[i].note_on_timestamp) == task_run.sequencer_run_timer)/* && (source[i].note != OVER_SIGN)*/) {
				
					if(second_seq[i].CH<6){
						
							if(second_seq[i].CH==STRING_LOW){
								
									if(task_run.current_tone!=6) Send_MIDI_Data_RAW(0xAC, second_seq[i].CH, 0x00);
									#ifdef CAPO_CHORD
									Send_MIDI_Data_RAW(0x88, capo_chord[task_run.chord_index][capo_chord[task_run.chord_index][6]]+task_run.key_index, second_seq[i].velocity);
									Send_MIDI_Data_RAW(0x98, capo_chord[task_run.chord_index][capo_chord[task_run.chord_index][6]]+task_run.key_index, second_seq[i].velocity);
									#else
									Send_MIDI_Data_RAW(0x88, chord[major[task_run.key_index][task_run.chord_index]][chord[major[task_run.key_index][task_run.chord_index]][6]], vel_pre_deal(second_seq[i].velocity));
									Send_MIDI_Data_RAW(0x98, chord[major[task_run.key_index][task_run.chord_index]][chord[major[task_run.key_index][task_run.chord_index]][6]], vel_pre_deal(second_seq[i].velocity));
									#endif
							
							}
							else{
								if(task_run.current_tone!=6) Send_MIDI_Data_RAW(0xAC, second_seq[i].CH, 0x00);
								#ifdef CAPO_CHORD
								Send_MIDI_Data_RAW(0x88, capo_chord[task_run.chord_index][second_seq[i].CH], second_seq[i].velocity);
								Send_MIDI_Data_RAW(0x98, capo_chord[task_run.chord_index][second_seq[i].CH], second_seq[i].velocity);
								#else
								Send_MIDI_Data_RAW(0x88, chord[major[task_run.key_index][task_run.chord_index]][second_seq[i].CH], vel_pre_deal(second_seq[i].velocity));
								Send_MIDI_Data_RAW(0x98, chord[major[task_run.key_index][task_run.chord_index]][second_seq[i].CH], vel_pre_deal(second_seq[i].velocity));
								#endif
							}
							
					}else if(second_seq[i].CH==HALF)
					{
						
								task_run.half_count2 = i;
					
					}
					else  if(second_seq[i].CH>5){
								
							//	if(task_run.chord_index>7)	task_run.chord_index = task_run.chord_index-7;
								
								tech_handle(second_seq[i].CH,vel_pre_deal(second_seq[i].velocity));
						
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
}





void Halt_auto_mode(void)
{
		if(task_run.play_type)task_run.rhythm_index=1;
		else task_run.rhythm_index=0;
		
	  sequencer_rhythm_source_t *source;
		task_run.total = rhythm_Source[0].main_source[task_run.rhythm_index].total-1;
	  source = (sequencer_rhythm_source_t *)rhythm_Source[0].main_source[task_run.rhythm_index].source;
		if(task_run.enable){
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
							
						#ifdef CAPO_CHORD
							Send_MIDI_Data_RAW(0x80|source[task_run.bit_count].CH, capo_chord[task_run.chord_index][capo_chord[task_run.chord_index][6]]+task_run.key_index, source[task_run.bit_count].velocity);
							Send_MIDI_Data_RAW(0x90|source[task_run.bit_count].CH, capo_chord[task_run.chord_index][capo_chord[task_run.chord_index][6]]+task_run.key_index, source[task_run.bit_count].velocity);
						#else
							Send_MIDI_Data_RAW(0x80|source[task_run.bit_count].CH, chord[major[task_run.key_index][task_run.chord_index]][chord[major[task_run.key_index][task_run.chord_index]][6]], source[task_run.bit_count].velocity);
							Send_MIDI_Data_RAW(0x90|source[task_run.bit_count].CH, chord[major[task_run.key_index][task_run.chord_index]][chord[major[task_run.key_index][task_run.chord_index]][6]], source[task_run.bit_count].velocity);
						#endif
							
						}else{
							if(task_run.bit_count>task_run.total)task_run.bit_count=0;
							#ifdef CAPO_CHORD
							Send_MIDI_Data_RAW(0x80|source[task_run.bit_count].CH, capo_chord[task_run.chord_index][source[task_run.bit_count].CH]+task_run.key_index, source[task_run.bit_count].velocity);						
							Send_MIDI_Data_RAW(0x90|source[task_run.bit_count].CH, capo_chord[task_run.chord_index][source[task_run.bit_count].CH]+task_run.key_index, source[task_run.bit_count].velocity);
							#else
							Send_MIDI_Data_RAW(0x80|source[task_run.bit_count].CH, chord[major[task_run.key_index][task_run.chord_index]][source[task_run.bit_count].CH], source[task_run.bit_count].velocity);						
							Send_MIDI_Data_RAW(0x90|source[task_run.bit_count].CH, chord[major[task_run.key_index][task_run.chord_index]][source[task_run.bit_count].CH], source[task_run.bit_count].velocity);
							#endif
						}
						
						
					}else{
							//if(task_run.bit_count>task_run.total)task_run.bit_count=0;
							if(source[task_run.bit_count].CH==NoteOffAll) task_run.bit_count++;
							tech_handle(source[task_run.bit_count].CH,source[task_run.bit_count].velocity);
							
					}
					
					if(task_run.next_bit-source[task_run.bit_count].note_on_timestamp>20||task_run.bit_count==task_run.total){
							
							
							sequencer_stop();	
							
					} 
							
		 }
		task_run.bit_count++;
		
	 }
			
}


void one_chord_mode()
{
	

	
		if(task_run.play_type)task_run.rhythm_index=1;
		else task_run.rhythm_index = 0;
		
		
	
		if(task_run.chord_index>ONECHORD_COUNT-1) 
			return;
	
	  task_run.total = rhythm_Source[task_run.current_tone].main_source[task_run.rhythm_index].total;
		sequencer_rhythm_source_t *source;
	  source = (sequencer_rhythm_source_t *)rhythm_Source[task_run.current_tone].main_source[task_run.rhythm_index].source;
	
		task_run.second_seq_total = rhythm_Source[task_run.current_tone].second_source[task_run.rhythm2_index].total;
		sequencer_rhythm_source_t *second_seq;
		second_seq = (sequencer_rhythm_source_t *)rhythm_Source[task_run.current_tone].second_source[task_run.rhythm2_index].source;
		
	  if(task_run.enable&&task_run.sequencer_state){
		
		//if(task_run.sequencer_state){
					
				
		//}
//		for (uint8_t i = 0; i < task_run.total; i++)
//	    if(source[i].CH==HALF )task_run.half_count = i;
//		
//		
		if(task_run.halt_mode)
		{
				for (uint8_t i = 0; i < task_run.total; i++)if(source[i].CH==HALF )task_run.half_count = i;
				if(task_run.half_flag&&(task_run.last_chord==task_run.chord_index||task_run.first_flag)){
				
					
					task_run.start = task_run.half_count;
					task_run.over = task_run.total;
				}else{
					task_run.start = 0;
					task_run.over = task_run.half_count;
				
				}
					
		
		}else{
					task_run.start = 0;
					task_run.over = task_run.total;	
		}
	//	task_run.over_index = task_run.total;

		for (uint8_t i = task_run.start; i <task_run.over; i++){
			
			
			if (((uint16_t)(source[i].note_on_timestamp) == task_run.sequencer_run_timer)/* && (source[i].note != OVER_SIGN)*/) {
				
					if(source[i].CH<6){
						
							if(source[i].CH==STRING_LOW){
								
		
							
								Send_MIDI_Data_RAW(0x80|source[i].CH, task_run.one_chord[task_run.one_chord[6]],  vel_pre_deal(source[i].velocity));
								Send_MIDI_Data_RAW(0x90|source[i].CH, task_run.one_chord[task_run.one_chord[6]], vel_pre_deal(source[i].velocity));
								
						
							}
							else{
							//	Send_MIDI_Data_RAW(0xa0,0,task_run.vel);
					
							
									Send_MIDI_Data_RAW(0x80|source[i].CH,  task_run.one_chord[source[i].CH],  vel_pre_deal(source[i].velocity));
									Send_MIDI_Data_RAW(0x90|source[i].CH,  task_run.one_chord[source[i].CH],  vel_pre_deal(source[i].velocity));
									
				
							}
							
					}else if(source[i].CH==HALF)
					{
						
								//task_run.half_count = i;
		
								
					}else  if(source[i].CH>5){
								
							//	if(task_run.chord_index>7)	task_run.chord_index = task_run.chord_index-7;
								tech_handle(source[i].CH,vel_pre_deal(source[i].velocity));
						
					}
					
//					if(i== task_run.over-1){
//							
//						//	task_run.sequencer_run_timer = 0;
//							task_run.sequencer_state = 0;
//					
//					}
					
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
				
		

				
    }
		

	if(task_run.second_seq_on_off==1){	
		
		
		
		if(task_run.halt_mode)
		{
				for (uint8_t i = 0; i < task_run.second_seq_total; i++)
				if(second_seq[i].CH==HALF ) task_run.half_count2 = i;
				if(task_run.half_flag){
					
					task_run.start2 = task_run.half_count2;
					task_run.over2 = task_run.second_seq_total;
				}else{
					task_run.start2 = 0;
					task_run.over2 = task_run.half_count2;
				
				}
					
		
		}else{
					task_run.start2 = 0;
					task_run.over2 = task_run.second_seq_total;	
		}
		
		for (uint16_t i = task_run.start2; i <task_run.over2; i++){
  
			if (((uint16_t)(second_seq[i].note_on_timestamp) == task_run.sequencer_run_timer)/* && (source[i].note != OVER_SIGN)*/) {
				
					if(second_seq[i].CH<6){
						
							if(second_seq[i].CH==STRING_LOW){
								
									if(task_run.current_tone!=6) Send_MIDI_Data_RAW(0xAC, second_seq[i].CH, 0x00);
					
									Send_MIDI_Data_RAW(0x88, task_run.one_chord[task_run.one_chord[6]], second_seq[i].velocity);
									Send_MIDI_Data_RAW(0x98, task_run.one_chord[task_run.one_chord[6]], second_seq[i].velocity);
				
							
							}
							else{
								if(task_run.current_tone!=6) Send_MIDI_Data_RAW(0xAC, second_seq[i].CH, 0x00);
							
								Send_MIDI_Data_RAW(0x88, task_run.one_chord[task_run.one_chord[6]], second_seq[i].velocity);
								Send_MIDI_Data_RAW(0x98, task_run.one_chord[task_run.one_chord[6]], second_seq[i].velocity);
			
							}
							
					}else if(second_seq[i].CH==HALF)
					{
						
								task_run.half_count2 = i;
					
					}
					else  if(second_seq[i].CH>5){
								
							//	if(task_run.chord_index>7)	task_run.chord_index = task_run.chord_index-7;
								
								tech_handle(second_seq[i].CH,vel_pre_deal(second_seq[i].velocity));
						
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
}



Mode_Setting_t mode_Setting[] = {

			{0,Auto_mode},
			//{1,Halt_auto_mode},
			{1,one_chord_mode},
	
			
};


