#ifndef __SEQUENCER_SOURCE_H__
#define __SEQUENCER_SOURCE_H__

#include "stdint.h"

#include "sequencer.h"

#include "seq_conf.h"



#define RHYTHM_SOURCE_MAX_COUNT 120
#define PAVING_SOURCE_MAX_COUNT 50

//1  2  3  4  5  6  7  8  9  10  11  12
//C #C  D #D  E  F #F  G #G   A  #A  B

//1     3-2  5-2  6    8    10-2   1-4
//135134 
#ifdef CAPO_CHORD

const uint8_t capo_chord[7][7] = {
	
	{0xFF,0x30,0x34,0x37,0x3C,0x40,1}, 	
	{0xFF,0xFF,0x32,0x39,0x3E,0x41,2},
	{0x28,0x2F,0x34,0x37,0x3B,0x40,0},
	{0x29,0x30,0x35,0x39,0x3C,0x41,0},	
	{0x2B,0x2F,0x32,0x37,0x3B,0x43,0},	
	{0xFF,0x2D,0x34,0x39,0x3C,0x40,1},	
	{0x2B,0x2F,0x32,0x37,0x3B,0x41,0},	
	
};




#else
const uint8_t chord[37][7] = { 

	{0xFF,0x30,0x34,0x37,0x3C,0x40,1}, 				//C   0
	{0xFF,0x30,0x37,0x3C,0x3F,0x43,1},				//Cm	1
	{0xFF,0x31,0x38,0x3D,0x41,0x44,1},				//#C	2
	{0xFF,0x31,0x38,0x3D,0x40,0x44,1},				//#Cm	3
	{0xFF,0x30,0x34,0x3A,0x3C,0x40,1},			  //C7	4
	{0xFF,0xFF,0x32,0x39,0x3E,0x42,2},				//D		5
	{0xFF,0xFF,0x32,0x39,0x3E,0x41,2},				//Dm	6
	{0xFF,0x32,0x3A,0x3F,0x42,0x46,2},				//#Dm	7
	{0xFF,0xFF,0x32,0x39,0x3C,0x42,2},				//D7	8
	{0x28,0x2F,0x34,0x38,0x3B,0x40,0},				//E		9
	{0x28,0x2F,0x34,0x37,0x3B,0x40,0},				//Em	10
	{0x28,0x2F,0x32,0x38,0x3B,0x40,0},				//E7	11
	{0x29,0x30,0x35,0x39,0x3C,0x41,0},				//F		12
	{0x29,0x30,0x35,0x38,0x3C,0x41,0},				//Fm	13
	{0x2A,0x31,0x36,0x3A,0x3D,0x42,0},				//#F	14
	{0x2A,0x31,0x36,0x39,0x3D,0x42,0},				//#Fm	15
	{0x2A,0x31,0x34,0x3A,0x3D,0x42,0},				//#F7	16
	{0x2B,0x2F,0x32,0x37,0x3B,0x43,0},				//G		17
	{0x2B,0x32,0x37,0x3B,0x3E,0x43,0},				//Gm	18
	{0x2C,0x33,0x38,0x3C,0x3F,0x44,0},				//#G	19
	{0x2C,0x33,0x38,0x3C,0x3F,0x44,0},				//#Gm	20
	{0x2B,0x2F,0x32,0x37,0x3B,0x41,0},				//G7	21
	{0xFF,0x2D,0x34,0x39,0x3D,0x40,1},				//A		22
	{0xFF,0x2D,0x34,0x39,0x3C,0x40,1},				//Am	23
	{0x29,0x2E,0x35,0x3A,0x3E,0x41,0},				//#A	24
	{0x29,0x2E,0x35,0x3A,0x3D,0x41,0},				//#Am	25
	{0xFF,0x2D,0x34,0x37,0x3D,0x40,1},				//A7	26
	{0xFF,0x2F,0x36,0x3B,0x3F,0x42,1},				//B		27
	{0xFF,0x2F,0x36,0x3B,0x3E,0x42,1},				//Bm	28
	{0xFF,0x2F,0x36,0x39,0x3F,0x42,1},				//B7	29
	{0xFF,0x2F,0x36,0x38,0x3E,0x42,1},				//Bm7	30
	{0x2C,0x33,0x36,0x3C,0x3F,0x44,0},				//#G7 31
	{0xFF,0x33,0X3A,0x3F,0x43,0x46,1},				//#D	32
	{0xFF,0x2E,0x35,0x37,0x3E,0x41,1},				//#A7 33
	{0xFF,0x31,0x38,0x3B,0x40,0x44,1},				//#C7 34
	{0xFF,0x33,0X3A,0x3D,0x43,0x46,1},				//#D7 35
	{0x29,0x30,0x33,0x39,0x3C,0x41,0},				//#F7 36
	

};


uint8_t major[12][7] = {
	
		{0,6,10,12,17,23,21},					//C
		{2,7,13,14,19,24,31},					//C#
		{5,10,15,17,22,28,26},				//D
		{32,13,18,19,24,1,33},				//D#
		{9,15,20,22,27,3,29},					//E
		{12,18,23,24,0,6,4},					//F
		{14,20,25,27,2,7,34},					//F#
		{17,23,28,0,5,10,8},					//G
		{19,25,1,2,32,13,35},					//G#
		{22,28,3,5,9,15,11},					//A
		{24,1,6,32,12,18,36},					//A#
		{27,3,7,9,14,20,16},					//B
		
		
};

#endif

sequencer_rhythm_source_t tguitar1[RHYTHM_SOURCE_MAX_COUNT] = {

		{67,STRING_LOW,0,255},
		{51,STRING_3,250,255},
		{65,STRING_2,500,255},
		{52,STRING_3,750,255},
		{0,HALF,1000,0},
		{82,STRING_1,1000,255},
		
		{46,STRING_3,1250,255},
		{57,STRING_2,1500,255},
		{40,STRING_3,1750,255},
 		
		

};



sequencer_rhythm_source_t tguitar2[RHYTHM_SOURCE_MAX_COUNT] = {

{51,SWEEP_D1,0,255},
{54,STRING_LOW,0,255},
{57,STRING_5,5,255},
{62,STRING_4,10,255},
{58,STRING_3,15,255},
{63,STRING_2,20,255},
{45,STRING_1,25,255},
{112,SYCOPATION,500,250},
{54,STRING_1,750,250},
{40,SWEEP_U1,750,250},
{54,STRING_2,755,250},
{54,STRING_3,760,250},
{54,STRING_4,765,250},
{55,STRING_5,770,250},
{54,STRING_LOW,775,250},
{0,HALF,1000,0},
{72,STRING_LOW,1000,255},
{71,STRING_LOW,1000,255},
{60,SWEEP_D1,1000,255},
{71,STRING_5,1005,255},
{71,STRING_5,1005,255},
{72,STRING_4,1010,255},
{73,STRING_4,1010,255},
{72,STRING_3,1015,255},
{73,STRING_3,1015,255},
{71,STRING_2,1020,255},
{70,STRING_2,1020,255},
{71,STRING_1,1025,255},
{72,STRING_1,1025,255},
{30,SWEEP_U1,1250,250},
{61,STRING_1,1250,250},
{61,STRING_2,1255,250},
{63,STRING_3,1260,250},
{63,STRING_4,1265,250},
{61,STRING_5,1270,250},
{62,STRING_LOW,1275,250},
{111,SYCOPATION,1500,250},
{53,SYCOPATION,1500,250},
{55,STRING_1,1750,250},
{30,SWEEP_U1,1750,250},
{30,SWEEP_U1,1750,250},
{30,STRING_1,1750,250},
{54,STRING_2,1755,250},
{55,STRING_2,1755,250},
{54,STRING_3,1760,250},
{54,STRING_3,1760,250},
{57,STRING_4,1765,250},
{54,STRING_4,1765,250},
{54,STRING_5,1770,250},
{54,STRING_5,1770,250},
{55,STRING_LOW,1775,250},
{54,STRING_LOW,1775,250},
};






sequencer_rhythm_source_t mguitar1[RHYTHM_SOURCE_MAX_COUNT] = {

		{67,STRING_LOW,0,255},
		{51,STRING_3,250,255},
		{65,STRING_2,500,255},
		{52,STRING_3,750,255},
		{0,HALF,1000,0},
		{82,STRING_1,1000,255},

		{46,STRING_3,1250,255},
		{57,STRING_2,1500,255},
		{40,STRING_3,1750,255},

};


sequencer_rhythm_source_t mguitar2[RHYTHM_SOURCE_MAX_COUNT] = {

{51,SWEEP_D1,0,255},
{54,STRING_LOW,0,255},
{57,STRING_5,5,255},
{62,STRING_4,10,255},
{58,STRING_3,15,255},
{63,STRING_2,20,255},
{45,STRING_1,25,255},
{112,SYCOPATION,500,250},
{54,STRING_1,750,250},
{40,SWEEP_U1,750,250},
{54,STRING_2,755,250},
{54,STRING_3,760,250},
{54,STRING_4,765,250},
{55,STRING_5,770,250},
{54,STRING_LOW,775,250},
{0,HALF,1000,0},
{72,STRING_LOW,1000,255},
{71,STRING_LOW,1000,255},
{60,SWEEP_D1,1000,255},
{71,STRING_5,1005,255},
{71,STRING_5,1005,255},
{72,STRING_4,1010,255},
{73,STRING_4,1010,255},
{72,STRING_3,1015,255},
{73,STRING_3,1015,255},
{71,STRING_2,1020,255},
{70,STRING_2,1020,255},
{71,STRING_1,1025,255},
{72,STRING_1,1025,255},
{30,SWEEP_U1,1250,250},
{61,STRING_1,1250,250},
{61,STRING_2,1255,250},
{63,STRING_3,1260,250},
{63,STRING_4,1265,250},
{61,STRING_5,1270,250},
{62,STRING_LOW,1275,250},
{111,SYCOPATION,1500,250},
{53,SYCOPATION,1500,250},
{55,STRING_1,1750,250},
{30,SWEEP_U1,1750,250},
{30,SWEEP_U1,1750,250},
{30,STRING_1,1750,250},
{54,STRING_2,1755,250},
{55,STRING_2,1755,250},
{54,STRING_3,1760,250},
{54,STRING_3,1760,250},
{57,STRING_4,1765,250},
{54,STRING_4,1765,250},
{54,STRING_5,1770,250},
{54,STRING_5,1770,250},
{55,STRING_LOW,1775,250},
{54,STRING_LOW,1775,250},
 

};




sequencer_rhythm_source_t tcguitar1[RHYTHM_SOURCE_MAX_COUNT] = {

{70,STRING_LOW,0,255},
{40,STRING_3,250,250},
{50,STRING_2,500,250},
{59,STRING_3,750,125},
{66,STRING_2,750,125},
{67,STRING_4,750,125},
{50,STRING_1,750,125},
{0,HALF,1000,0},
{70,STRING_LOW,1001,255},
{40,STRING_3,1250,250},
{50,STRING_2,1500,250},
{59,STRING_3,1750,125},
{66,STRING_2,1750,125},
{67,STRING_4,1750,125},
{50,STRING_1,1750,125},
  
 

};

sequencer_rhythm_source_t tcguitar2[RHYTHM_SOURCE_MAX_COUNT] = {

{65,STRING_LOW,0,255},
{52,STRING_3,250,255},
{63,STRING_2,500,255},
{81,STRING_1,750,255},
{53,STRING_2,1000,255},
{32,STRING_3,1250,255},
{0,HALF,1500,0},
{65,STRING_LOW,1500,255},
{52,STRING_3,1750,255},
{63,STRING_2,2000,255},
{81,STRING_1,2250,255},
{53,STRING_2,2500,255},
{32,STRING_3,2750,255},
 

};

sequencer_rhythm_source_t piano1[RHYTHM_SOURCE_MAX_COUNT] = {

{58,STRING_3,0,255},
{47,STRING_2,0,255},
{54,STRING_1,0,255},
{40,STRING_LOW,0,255},
{13,STRING_LOW,500,255},
{32,STRING_1,500,255},
{27,STRING_2,500,255},
{36,STRING_3,500,255},
{34,STRING_1,1000,255},
{34,STRING_LOW,1000,255},
{26,STRING_3,1000,255},
{39,STRING_2,1000,255},
{0,HALF,1000,0},
{41,STRING_2,1500,255},
{52,STRING_LOW,1500,255},
{46,STRING_3,1500,255},
{48,STRING_1,1500,255},
 

};

sequencer_rhythm_source_t piano2[RHYTHM_SOURCE_MAX_COUNT] = {

{80,STRING_LOW,0,255},
{60,STRING_3,250,255},
{70,STRING_1,500,255},
{40,STRING_2,750,255},
{40,STRING_2,1000,255},
{40,STRING_1,1000,255},
{0,HALF,1000,0},
{40,STRING_3,1000,255},
{40,STRING_LOW,1000,255},
{70,STRING_1,1500,255},
{40,STRING_2,1750,255},

};


sequencer_rhythm_source_t gdguitar1[RHYTHM_SOURCE_MAX_COUNT] = {

{63,STRING_LOW,0,255},
{32,STRING_2,250,250},
{19,STRING_3,250,250},
{25,STRING_1,250,250},
{24,STRING_3,500,255},
{37,STRING_2,500,255},
{29,STRING_1,500,255},
{48,STRING_2,750,250},
{43,STRING_3,750,250},
{51,STRING_1,750,250},
{0,HALF,750,0},
{29,STRING_3,1000,250},
{19,STRING_1,1000,250},
{32,STRING_2,1000,250},
{50,STRING_1,1250,255},
{45,STRING_2,1250,255},
{39,STRING_3,1250,255},
};

sequencer_rhythm_source_t gdguitar2[RHYTHM_SOURCE_MAX_COUNT] = {

{63,STRING_LOW,0,255},
{32,STRING_2,250,250},
{19,STRING_3,250,250},
{25,STRING_1,250,250},
{24,STRING_3,500,255},
{37,STRING_2,500,255},
{29,STRING_1,500,255},
{48,STRING_2,750,250},
{43,STRING_3,750,250},
{51,STRING_1,750,250},
{29,STRING_3,1000,250},
{19,STRING_1,1000,250},
{32,STRING_2,1000,250},
{50,STRING_1,1250,255},
{45,STRING_2,1250,255},
{39,STRING_3,1250,255},
{0,HALF,1500,0},
{63,STRING_LOW,1500,255},
{32,STRING_2,1750,250},
{19,STRING_3,1750,250},
{25,STRING_1,1750,250},
{24,STRING_3,2000,255},
{37,STRING_2,2000,255},
{29,STRING_1,2000,255},
{48,STRING_2,2250,250},
{43,STRING_3,2250,250},
{51,STRING_1,2250,250},
{29,STRING_3,2500,250},
{19,STRING_1,2500,250},
{32,STRING_2,2500,250},
{50,STRING_1,2750,255},
{45,STRING_2,2750,255},
{39,STRING_3,2750,255},




};

sequencer_rhythm_source_t banjor1[RHYTHM_SOURCE_MAX_COUNT] = {

{92,STRING_LOW,0,68},
{98,STRING_2,62,57},
{101,STRING_3,124,62},
{109,STRING_2,186,57},
{107,STRING_1,243,57},
{119,STRING_3,310,57},
{118,STRING_2,372,57},
{114,STRING_1,429,62},
{95,STRING_LOW,497,47},
{119,STRING_2,559,57},
{103,STRING_3,621,62},
{111,STRING_2,678,57},
{110,STRING_1,740,62},
{123,STRING_3,802,57},
{118,STRING_2,864,26},
{113,STRING_1,926,57},

{100,HALF,994,31},
{89,STRING_LOW,1000,57},
{120,STRING_2,1051,57},
{113,STRING_3,1113,62},
{115,STRING_2,1175,62},
{101,STRING_1,1237,57},
{100,STRING_3,1299,57},
{109,STRING_2,1361,57},
{115,STRING_1,1423,57},
{93,STRING_LOW,1485,10},
{123,STRING_2,1547,57},
{110,STRING_3,1609,120},
{117,STRING_2,1671,115},
{112,STRING_1,1733,115},
{123,STRING_3,1863,115},


};

sequencer_rhythm_source_t banjor2[RHYTHM_SOURCE_MAX_COUNT] = {


0

};

sequencer_rhythm_source_t dy1[RHYTHM_SOURCE_MAX_COUNT] = {

	
{90,STRING_LOW,0,115},
{92,STRING_3,125,36},
{89,STRING_2,250,120},
{88,STRING_3,375,26},
{80,STRING_LOW,500,120},
{95,STRING_3,625,42},
{93,STRING_2,750,16},
{80,STRING_3,865,16},
{98,HALF,1001,120},
{98,STRING_LOW,1001,120},
{93,STRING_3,1126,36},
{94,STRING_2,1251,120},
{77,STRING_3,1376,21},
{95,STRING_LOW,1501,21},
{88,STRING_3,1626,31},
{103,STRING_2,1751,120},
{96,STRING_3,1876,31},
	
};

sequencer_rhythm_source_t dy2[RHYTHM_SOURCE_MAX_COUNT] = {
	
0
};

sequencer_rhythm_source_t hcguitar1[RHYTHM_SOURCE_MAX_COUNT] = {
	
{70,STRING_LOW,0,255},
{40,STRING_3,250,250},
{50,STRING_2,500,250},
{59,STRING_3,750,125},
{66,STRING_2,750,125},
{67,STRING_4,750,125},
{50,STRING_1,750,125},
{0,HALF,1000,0},
{70,STRING_LOW,1001,255},
{40,STRING_3,1250,250},
{50,STRING_2,1500,250},
{59,STRING_3,1750,125},
{66,STRING_2,1750,125},
{67,STRING_4,1750,125},
{50,STRING_1,1750,125},
	
};

sequencer_rhythm_source_t hcguitar2[RHYTHM_SOURCE_MAX_COUNT] = {
	
{65,STRING_LOW,0,255},
{52,STRING_3,250,255},
{63,STRING_2,500,255},
{81,STRING_1,750,255},
{53,STRING_2,1000,255},
{32,STRING_3,1250,255},
{0,HALF,1500,0},
{65,STRING_LOW,1500,255},
{52,STRING_3,1750,255},
{63,STRING_2,2000,255},
{81,STRING_1,2250,255},
{53,STRING_2,2500,255},
{32,STRING_3,2750,255},
	
};


sequencer_rhythm_source_t bass_seq1[RHYTHM_SOURCE_MAX_COUNT] = {

{74,STRING_LOW,0,265},
{81,STRING_LOW,494,62},
{1,HALF,999,125},
{66,STRING_LOW,1243,98},
{83,STRING_LOW,1492,447},

};


sequencer_rhythm_source_t bass_seq2[RHYTHM_SOURCE_MAX_COUNT] = {
			
		
{82,STRING_LOW,0,239},
{79,STRING_LOW,249,244},
{82,STRING_LOW,498,239},
{79,STRING_LOW,747,244},
{1,HALF,996,125},
{82,STRING_LOW,996,114},
{79,STRING_LOW,1245,244},
{82,STRING_LOW,1494,239},
{79,STRING_LOW,1743,244},
			
			
};

sequencer_rhythm_source_t paving1[PAVING_SOURCE_MAX_COUNT] = {

{34,STRING_LOW,0,265},
{41,STRING_LOW,494,62},
{1,HALF,999,125},
{26,STRING_LOW,1243,98},
{43,STRING_LOW,1492,447},


};

sequencer_rhythm_source_t paving2[PAVING_SOURCE_MAX_COUNT] = {

{35,STRING_LOW,0,1130},
{20,STRING_LOW,1244,203},
{1,HALF,1499,125},
{16,STRING_LOW,1499,1062},
{11,STRING_LOW,2748,239},

};

sequencer_rhythm_source_t paving3[PAVING_SOURCE_MAX_COUNT] = {

{34,STRING_LOW,5,916},
{28,STRING_LOW,993,72},
{1,HALF,1497,125},
{33,STRING_LOW,1497,796},
{28,STRING_LOW,2496,83},

};

sequencer_rhythm_source_t paving4[PAVING_SOURCE_MAX_COUNT] = {

{32,STRING_LOW,0,239},
{29,STRING_LOW,249,244},
{32,STRING_LOW,498,239},
{29,STRING_LOW,747,244},
{1,HALF,996,125},
{32,STRING_LOW,996,114},
{29,STRING_LOW,1245,244},
{32,STRING_LOW,1494,239},
{29,STRING_LOW,1743,244},
};

sequencer_rhythm_source_t paving5[PAVING_SOURCE_MAX_COUNT] = {

{47,STRING_LOW,0,484},
{19,STRING_LOW,499,484},
{39,STRING_LOW,998,406},
{1,HALF,998,83},
{33,STRING_LOW,1492,333},
{35,STRING_LOW,1830,88},

};

sequencer_rhythm_source_t paving6[PAVING_SOURCE_MAX_COUNT] = {

{39,STRING_LOW,0,359},
{1,HALF,1000,125},
{33,STRING_LOW,1494,489},

};


sequencer_rhythm_source_info_t sequencer_rhythm_mguitar_source[M_GUITAR] = {
		

				{0,9,70,mguitar1},	
		
				{0,53,90,mguitar2},	

};



sequencer_rhythm_source_info_t sequencer_rhythm_tcguitar_source[2] = {
		

				{0,15,90,tcguitar1},	
				{0,13,90,tcguitar2},	
		
		
};


sequencer_rhythm_source_info_t sequencer_rhythm_hcguitar_source[2] = {
		

				{0,15,90,hcguitar1},	
				{0,13,90,hcguitar2},	
		
		
};

sequencer_rhythm_source_info_t sequencer_rhythm_gdguitar_source[2] = {
		

				{0,17,90,gdguitar1},	
				{0,33,90,gdguitar2},	
				
		
		
};
sequencer_rhythm_source_info_t sequencer_rhythm_piano_source[2] = {
		

		
				{0,17,90,piano1},	
				{0,11,90,piano2},	
		
		
};

sequencer_rhythm_source_info_t sequencer_rhythm_banjor_source[2] = {
		

		
				{0,31,90,banjor1},	
				{0,47,90,banjor2},	
		
		
};

sequencer_rhythm_source_info_t sequencer_rhythm_dy_source[2] = {
		

		
				{0,17,90,dy1},	
				{0,47,90,dy2},	
		
		
};

sequencer_rhythm_source_info_t sequencer_rhythm_tguitar_source[2] = {
		

		
				{0,9,90,tguitar1},	
				{0,53,90,tguitar2},	
		
		
};

sequencer_rhythm_source_info_t sequencer_rhythm_bass_seq[2] = {
		

		{0,5,90,bass_seq1},
		{0,9,119,bass_seq2},
//	{4,90,second_seq3},
		
		
					
		
		
};


sequencer_rhythm_source_info_t sequencer_rhythm_bass_paving_seq[6] = {
		

		{0,5,90,paving1},
		{0,5,90,paving2},
		{0,5,125,paving3},
		{0,9,119,paving4},
		{0,6,110,paving5},
		{0,3,75,paving6},

};




//每个音色对应的铺底音色
Rhythm_Source rhythm_Source[TONE_COUNT] = {
	
	
	

					{	sequencer_rhythm_mguitar_source,  sequencer_rhythm_bass_paving_seq},
					
					{	sequencer_rhythm_tguitar_source,  sequencer_rhythm_bass_paving_seq},
					
					{	sequencer_rhythm_tcguitar_source,  sequencer_rhythm_bass_paving_seq},
					
					
					{	sequencer_rhythm_hcguitar_source,  sequencer_rhythm_bass_paving_seq},
					
					{	sequencer_rhythm_gdguitar_source,  sequencer_rhythm_bass_paving_seq},
					
					{	sequencer_rhythm_piano_source,  sequencer_rhythm_bass_paving_seq},
					
					{	sequencer_rhythm_bass_seq, sequencer_rhythm_bass_paving_seq},
					
					{	sequencer_rhythm_banjor_source,  sequencer_rhythm_bass_paving_seq},
					
					{	sequencer_rhythm_dy_source, sequencer_rhythm_bass_paving_seq},
					

					



};




#endif