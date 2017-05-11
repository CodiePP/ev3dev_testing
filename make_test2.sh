#!/bin/sh

NAME=test2

GTEST_DIR=github__google__googletest.git/googletest/
GMOCK_DIR=github__google__googletest.git/googlemock/
EV3DEV_DIR=github__ddemidov__ev3dev-lang-cpp.git/

g++ -o ${NAME} -pthread ${NAME}.cpp\
  -isystem ${EV3DEV_DIR}\
  -isystem ${GTEST_DIR}/include\
  -isystem ${GMOCK_DIR}/include\
  -I ${GTEST_DIR}/\
  -I ${GMOCK_DIR}/\
  ${GTEST_DIR}/src/gtest-all.cc\
  ${GMOCK_DIR}/src/gmock-all.cc\
  -g -O1\
  -std=c++11

