#ifndef _BG_LOOPER_SOURCE_H__
#define _BG_LOOPER_SOURCE_H__


#include "bg_looper_conf.h"



typedef struct{
	
	uint8_t vel;
	uint8_t note;
	uint8_t string;
	uint16_t start_time;
	uint16_t NoteOn_Time;

}Loop_note;


typedef struct{

	uint8_t total;
	uint8_t type;
	uint8_t tone;
	uint8_t bgm;
	Loop_note *loop_data;
	
}Loop_source;


Loop_note loop_ch0[MAX_LOOP_COUNT];
Loop_note loop_ch1[MAX_LOOP_COUNT];
Loop_note loop_ch2[MAX_LOOP_COUNT];
Loop_note loop_ch3[MAX_LOOP_COUNT];
Loop_note loop_ch4[MAX_LOOP_COUNT];
Loop_note loop_ch5[MAX_LOOP_COUNT];
Loop_note loop_ch6[MAX_LOOP_COUNT];
Loop_note loop_ch7[MAX_LOOP_COUNT];
Loop_note loop_ch8[MAX_LOOP_COUNT];
Loop_note loop_ch9[MAX_LOOP_COUNT];


Loop_source loop_source[MAX_CH] = {

	{0,0,0,0,loop_ch0},
	{0,0,0,0,loop_ch1},
	{0,0,0,0,loop_ch2},
	{0,0,0,0,loop_ch3},
	{0,0,0,0,loop_ch4},
	{0,0,0,0,loop_ch5},
	{0,0,0,0,loop_ch6},
	{0,0,0,0,loop_ch7},
	{0,0,0,0,loop_ch8},
	{0,0,0,0,loop_ch9},
	
};	
extern Loop_source loop_source[MAX_CH];
#endif