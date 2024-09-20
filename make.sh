#!/bin/bash

# 检查是否提供了参数
if [ $# -eq 0 ]; then
  # 没有参数时执行的命令
  cd ./build
  make 
elif [ $# -eq 1 ]; then
  arg=$1
  if [[ $arg == "menuconfig" ]]; then
    kconfig-mconf ./config/config.mk
  fi
fi