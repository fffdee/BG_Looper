#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include "bg_looper_conf.h"


void timer_handler(int signum) {
    printf("Timer expired\n");
    // 在这里添加你的代码，比如更新状态、处理数据等
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
    // 主循环，这里程序会无限循环等待定时器到期
    while (1) {
        // 等待定时器到期
        pause(); // 阻塞，直到定时器到期或接收到信号
    }
}