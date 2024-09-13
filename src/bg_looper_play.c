/*****************************************************
 mmmmmm                           mmmm     mmmm   
 ##""""##                       ##""""#   ##""##   
 ##    ##   m#####m  ##m####m  ##        ##    ## 
 #######    " mmm##  ##"   ##  ##  mmmm  ##    ## 
 ##    ##  m##"""##  ##    ##  ##  ""##  ##    ## 
 ##mmmm##  ##mmm###  ##    ##   ##mmm##   ##mm##  
 """""""    """" ""  ""    ""     """"     """"   
******************************************************
  funstion: Main component of BG_Looper
	author  : BanGO
******************************************************/
#include <stdint.h>
#include <stdio.h>
#include "bg_looper_play.h"
#include "bg_looper.h"

Last_note play_note[6];
void looper_set_tone(uint8_t tone){

  
  
}

void looper_play(uint8_t ch){


    looper_set_tone(loop_run_task.get_tone(ch));
    
    for(uint16_t i = 0; i<loop_run_task.get_total(ch); i++)
    {
      if(loop_run_data.loop_play_time[ch] == loop_run_task.get_loop_note(ch,i).start_time){

            #ifdef DEBUG
              printf("The play data:CH:%d string:%d,note :%d, vel:%d, start_time:%d, noteon\n"
              ,ch,loop_run_task.get_loop_note(ch,i).string
              ,loop_run_task.get_loop_note(ch,i).note
              ,loop_run_task.get_loop_note(ch,i).vel
              ,loop_run_task.get_loop_note(ch,i).start_time);
            #endif

            loop_run_data.play_noteon_time[ch][loop_run_task.get_loop_note(ch,i).string]++;
            
            if(i == loop_run_task.get_total(ch)-1) 
            loop_run_data.loop_play_time[ch]=0;

      }

      if(loop_run_data.play_noteon_time[ch][loop_run_task.get_loop_note(ch,i).string]
          ==loop_run_task.get_loop_note(ch,i).NoteOn_Time)
      {
            #ifdef DEBUG
              printf("The play data:CH:%d,Note_OFF string:%d\n"
              ,ch,loop_run_task.get_loop_note(ch,i).string);
            #endif
            loop_run_data.play_noteon_time[ch][loop_run_task.get_loop_note(ch,i).string] = 0;
          
        
      }   
      
    }
    
      for(uint8_t i = 0;i<6;i++)
        if(loop_run_data.play_noteon_time[ch][i]!=0)
          loop_run_data.play_noteon_time[ch][i]++;

    loop_run_data.loop_play_time[ch]++;

}


void looper_stop(uint8_t ch){

  loop_run_data.loop_play_time[ch] = 0;
  for(uint8_t i = 0;i<6;i++)
  loop_run_data.play_noteon_time[ch][i] = 0;
  loop_run_data.channel_state[ch] = INVALID;

}


