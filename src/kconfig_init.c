#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "kconfig_init.h"
typedef struct _Kconfig_param
{
    uint8_t param_count;
    uint8_t param_id[100];
    uint8_t param_value[100];
}Kconfig_param;
Kconfig_param kconfig_param;

uint8_t get_param_id(char* name){
    
}
void read_config(Kconfig_param *param) {
    // 假设 .config 文件位于项目目录中
    const char *config_path = "./.config";

    // 打开文件
    FILE *config_file = fopen(config_path, "r");
    if (config_file == NULL) {
        perror("Error opening config file");
        return 1;
    }

    // 读取文件内容
    char line[1024];
    while (fgets(line, sizeof(line), config_file)) {
        // 解析配置参数
        char *value = strchr(line, '=');
        if (value != NULL) {
            *value = '\0'; // 替换等号
            value++; // 跳过等号
            printf("Parameter: %s, Value: %d\n", line, value);
        }
    }

    // 关闭文件
    fclose(config_file);
}