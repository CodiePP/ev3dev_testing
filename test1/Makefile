
NAME=test1

GTEST_DIR=../github__google__googletest.git/googletest/
GMOCK_DIR=../github__google__googletest.git/googlemock/
EV3DEV_DIR=../github__ddemidov__ev3dev-lang-cpp.git/

DEBUGFLAG = -g -DMOCK_TEST
OPTFLAG = -O1 -pthread
CXXSTD = -std=c++11
INCLUDES = -I../src -isystem ${EV3DEV_DIR}\
           -isystem ${GTEST_DIR}/include -isystem ${GMOCK_DIR}/include\
           -I ${GTEST_DIR}/ -I ${GMOCK_DIR}/
CXXFLAGS = $(CXXSTD) $(OPTFLAG) $(DEBUGFLAG) $(INCLUDES)
LDFLAGS =

libsrc = ${EV3DEV_DIR}/ev3dev.cpp
testsrc = $(GTEST_DIR)/src/gtest-all.cc $(GMOCK_DIR)/src/gmock-all.cc

src = test.cpp

obj = $(src:.cpp=.o) $(libsrc:.cpp=.o) $(testsrc:.cc=.o)


$(NAME): $(obj)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(obj) $(NAME)

