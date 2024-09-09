#ifndef _BG_LOOPER_CONF_H__
#define _BG_LOOPER_CONF_H__

#define DEBUG                     1

#define NOTE_ON                   0x90
#define NOTE_OFF                  0x80

#define MAX_CH 			          10
#define MAX_LOOP_COUNT            200	
#define MAX_TONE                  9

#define STOP_ALL                  0
#define RECORDING                 1
#define PLAY                      2
#define RECORDING_STOP            3
#define PLAY_STOP                 4

#define INVALID                   0xFF

typedef enum {
    
    SUCCESS = 0,         // 通常0表示成功
    ERROR_INVALID_INPUT, // 无效输入
    ERROR_OUT_OF_CH_RANGE,  // 超出通道范围

} ErrorCode;



#endif