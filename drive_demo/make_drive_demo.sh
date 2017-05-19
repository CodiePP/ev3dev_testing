#!/bin/sh

NAME=drive_demo

CC=arm-linux-gnueabi-gcc-4.9
CXX=arm-linux-gnueabi-g++-4.9

EV3DEV_DIR=../github__ddemidov__ev3dev-lang-cpp.git/

DEBUGFLAG="-g"
OPTFLAG="-O1"
CXXSTD="-std=c++11"
CXXFLAGS="${CXXSTD} ${OPTFLAG} ${DEBUGFLAG}"


$CXX -o ${NAME} -pthread ${NAME}.cpp\
  -I../\
  ../drivecontrol.cpp\
  -isystem ${EV3DEV_DIR}\
  ${EV3DEV_DIR}/ev3dev.cpp\
  ${CXXFLAGS}

