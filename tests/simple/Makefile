## the name of the output file
NAME=test1

SRC_DIR=../../src
OBJ_DIR=obj
GTEST_DIR=../../github__google__googletest.git/googletest/
GMOCK_DIR=../../github__google__googletest.git/googlemock/
EV3DEV_DIR=../../github__ddemidov__ev3dev-lang-cpp.git/

DEBUGFLAG = -g -DMOCK_TEST
OPTFLAG = -O1 -pthread
CXXSTD = -std=c++11
INCLUDES = -I$(SRC_DIR) -isystem ${EV3DEV_DIR}\
           -isystem ${GTEST_DIR}/include -isystem ${GMOCK_DIR}/include\
           -I ${GTEST_DIR}/ -I ${GMOCK_DIR}/
CXXFLAGS = $(CXXSTD) $(OPTFLAG) $(DEBUGFLAG) $(INCLUDES)
LDFLAGS =

## source files
src = test.cpp

## include these source files
libsrc = ${EV3DEV_DIR}/ev3dev.cpp
testsrc = $(GTEST_DIR)/src/gtest-all.cc $(GMOCK_DIR)/src/gmock-all.cc



## nothing to change below this line
objs = $(addprefix $(OBJ_DIR)/, $(notdir $(src:%.cpp=%.o)))\
			 $(addprefix $(OBJ_DIR)/, $(notdir $(libsrc:%.cpp=%.o)))\
			 $(addprefix $(OBJ_DIR)/, $(notdir $(testsrc:%.cc=%.o)))


$(NAME): make_obj_dir $(objs)
	$(CXX) -o $@ $(objs) $(CXXFLAGS) $(LDFLAGS)


$(OBJ_DIR)/%.o : %.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

$(OBJ_DIR)/%.o : $(GTEST_DIR)/src/%.cc
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) $< -o $@

$(OBJ_DIR)/%.o : $(GMOCK_DIR)/src/%.cc
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) $< -o $@

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) $< -o $@

$(OBJ_DIR)/%.o : %.cpp
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) $< -o $@

$(OBJ_DIR)/%.o : $(EV3DEV_DIR)/%.cpp
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) $< -o $@

make_obj_dir:
	mkdir -p $(OBJ_DIR)

.PHONY: clean
clean:
	rm -f $(objs) $(NAME)
	rmdir $(OBJ_DIR)

