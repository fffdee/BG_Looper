
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
#include <stdio.h>
#include <ev.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include "bg_looper_conf.h"
#include "bg_looper_setting.h"

uint8_t note_flag[6];
char input_data[] = {'z','x','c','v','b','n'};
void input_handle(uint8_t input);

// ev_io watcher回调函数
void io_cb(struct ev_loop *loop, struct ev_io *w, int revents) {
    char ch;
    if (read(w->fd, &ch, 1) == 1) {
        printf("You pressed: %c\n", ch);
        // if (ch == 'q') {
        //     ev_break(loop, EVBREAK_ALL);
        // }
        input_handle(ch);
    }
}
void input_handle(uint8_t input)
{
    
    switch(input){

        case 'e':
        bg_looper.enable(1);
        break;

        case 'q':
        bg_looper.enable(0);
        break;

        case 'p':
        bg_looper.play(0);
        break;
            
        case 'r':
        bg_looper.record(0,0);
        break;

        case 's':
        bg_looper.stop_record(0);
        break;

        case 't':
        bg_looper.stop_play(0);
        break;

        case 0x0A:break;
        
        default:
        
        
        if(bg_looper.get_recording_state){

            for (uint8_t i = 0; i < 6; i++)
            {
               if( input == input_data[i])
               {
                    note_flag[i] =!note_flag[i];
                    printf(" the note is %d\n" ,note_flag[i]);
                    if(note_flag[i])
                        bg_looper.note_recorder(0x90|i,i*10,64);  
                    else
                        bg_looper.note_recorder(0x80|i,i*10,64); 
               }

               
            }
            
        }else
            printf("invalid input\n");
        break;

    }
}

void keyboard_init(){
    
    struct ev_loop *loop = ev_default_loop(0);
    struct ev_io w;

    // 打开标准输入
    w.fd = 0; // 0是标准输入的文件描述符
    ev_io_init(&w, io_cb, w.fd, EV_READ);
    ev_io_start(loop, &w);

    printf("Press 'q' to quit\n");

    // 开始事件循环
    ev_run(loop, 0);

    // 清理
    ev_io_stop(loop, &w);
    ev_loop_destroy(loop);

}

void timer_handler(int signum) {
    
    bg_looper.callback();
}

void time_init(){
    
    // 设置定时器，以1毫秒的间隔执行
    // 使用setitimer设置定时器
    struct itimerval itv;
    // 设置定时器间隔为1毫秒
    itv.it_interval.tv_sec = 0; // 0秒
    itv.it_interval.tv_usec = 1000; // 1000微秒（1毫秒）
    // 设置定时器首次到期的时间为0秒
    itv.it_value.tv_sec = 0;
    itv.it_value.tv_usec = 1000;

    // 启动信号处理程序
    signal(SIGALRM, timer_handler);

    // 设置定时器
    setitimer(ITIMER_REAL, &itv, NULL);

}
int main(void)
{
    
    time_init();
    keyboard_init();
    // 主循环，这里程序会无限循环等待定时器到期
    while (1) {
        // 等待定时器到期
        pause(); // 阻塞，直到定时器到期或接收到信号
    }
}