#ifndef _BG_LOOPER_CONF_H__
#define _BG_LOOPER_CONF_H__




#define MAX_CH 			10
#define MAX_LOOP_COUNT  200	
#define MAX_TONE        9

#define RECORDING       0
#define PLAY            1

typedef enum {
    
    SUCCESS = 0,         // 通常0表示成功
    ERROR_INVALID_INPUT, // 无效输入
    ERROR_OUT_OF_CH_RANGE,  // 超出通道范围

} ErrorCode;



#endif