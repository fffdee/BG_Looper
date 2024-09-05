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



#include "chord.h"



typedef struct{
		
		char* name;
		uint8_t intervallic[6];

}Chord_rule;

Chord_rule chord_rule[] = {

		{"3",{4,3,0,0,0,0}},
		{"m",{3,4,0,0,0,0}},
		{"+",{4,4,0,0,0,0}},
		{"°",{4,4,0,0,0,0}},
		{"maj7",{4,3,4,0,0,0}},
		{"m7",{3,4,3,0,0,0}},
		{"7",{3,4,3,0,0,0}},
		
		
		
		
		

};


typedef struct{
	
	uint8_t main_chord;   									
	uint8_t attribute;
	
	char* name;
	
  uint8_t O_data[6];
	
	
}AutoChordData;

typedef struct{
	
	uint8_t input;   									
	
  uint8_t mode;
	
	
}ChordInputData;

ChordInputData CIData = {0x10,0x00};     

void pretreatment(uint8_t input, uint8_t *main_chord, uint8_t *attribute)
{
			*main_chord = (input>>4)&0x0F;
			*attribute  = input&0x0F;
}

AutoChordData handle(ChordInputData CIData)
{
		AutoChordData ACData;
		
		pretreatment(CIData.input, &ACData.main_chord, &ACData.attribute);
	
	
		return ACData;
}






