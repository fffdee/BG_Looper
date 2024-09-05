#include "task_scheduler.h"


// #include <stdint.h>
// #include <stdbool.h>

// #define MAX_TASKS 10

// // 假设任务结构体
// typedef struct {
//     void (*task_func)(void*); // 任务函数指针
//     void *arg;                // 任务参数
//     bool running;             // 任务是否正在运行
// } task_t;

// // 任务队列
// task_t task_queue[MAX_TASKS];
// uint8_t task_count = 0;

// // 添加任务到队列
// bool add_task(void (*task_func)(void*), void *arg) {
//     if (task_count >= MAX_TASKS) {
//         return false; // 任务队列已满
//     }
    
//     task_queue[task_count].task_func = task_func;
//     task_queue[task_count].arg = arg;
//     task_queue[task_count].running = true;
//     task_count++;
    
//     return true;
// }

// // 结束任务
// bool end_task(void (*task_func)(void*)) {
//     for (uint8_t i = 0; i < task_count; i++) {
//         if (task_queue[i].task_func == task_func) {
//             task_queue[i].running = false;
//             return true;
//         }
//     }
//     return false; // 任务未找到
// }

// // 任务调度函数
// void task_scheduler(void) {
//     for (uint8_t i = 0; i < task_count; i++) {
//         if (task_queue[i].running) {
//             task_queue[i].task_func(task_queue[i].arg);
//         }
//     }
// }

// // 示例任务函数
// void example_task(void *arg) {
//     // 执行任务代码
// }

// int main(void) {
//     // 初始化任务队列
//     add_task(example_task, NULL);

//     while (1) {
//         // 调度任务
//         task_scheduler();
        
//         // 其他代码
        
//         // 假设在某个条件下结束任务
//         if (/* 某个条件 */) {
//             end_task(example_task);
//         }
//     }

//     return 0;
// }
