## the name of the output file
NAME=colorsensor_demo

SRC_DIR=../../src
OBJ_DIR=obj
EV3DEV_DIR=../../github__ddemidov__ev3dev-lang-cpp.git/

CC  = arm-linux-gnueabi-gcc-4.9
CXX = arm-linux-gnueabi-g++-4.9

DEBUGFLAG = -g -UMOCK_TEST
OPTFLAG = -O1 -pthread
CXXSTD = -std=c++11
INCLUDES = -I$(SRC_DIR) -isystem $(EV3DEV_DIR)
CXXFLAGS = $(CXXSTD) $(OPTFLAG) $(DEBUGFLAG) $(INCLUDES)
LDFLAGS =

## source files
src = colorsensor_demo.cpp

## include these source files
libsrc = $(EV3DEV_DIR)/ev3dev.cpp\
				 $(SRC_DIR)/colorsensor.cpp



## nothing to change below this line
objs = $(addprefix $(OBJ_DIR)/, $(notdir $(src:%.cpp=%.o)))\
			 $(addprefix $(OBJ_DIR)/, $(notdir $(libsrc:%.cpp=%.o)))


$(NAME): make_obj_dir $(objs)
	$(CXX) -o $@ $(objs) $(CXXFLAGS) $(LDFLAGS)


$(OBJ_DIR)/%.o : %.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

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

