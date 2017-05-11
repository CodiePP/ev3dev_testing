#!/bin/sh

NAME=test1

GTEST_DIR=github__google__googletest.git/googletest/
EV3DEV_DIR=github__ddemidov__ev3dev-lang-cpp.git/

g++ -o ${NAME} -pthread ${NAME}.cpp\
  -isystem ${EV3DEV_DIR}\
  -isystem ${GTEST_DIR}/include\
  -I ${GTEST_DIR}/\
  -I ${GMOCK_DIR}/\
  ${GTEST_DIR}/src/gtest-all.cc\
  ${EV3DEV_DIR}/ev3dev.cpp\
  -g -O1\
  -std=c++11

