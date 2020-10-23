.SUFFIXES : .x .o .c .s

DIR_INC = ../includes
DIR_LIB = ../libs
DIR_LIB_INC = $(DIR_LIB)/inc
DIR_COMMON = ../common
DIR_SERVER = ../server
DIR_CONFIG = ../config

INCLUDE = -I./ \
		  -I$(DIR_INC) \
		  -I$(DIR_LIB_INC) \
		  -I$(DIR_COMMON) \
		  -I$(DIR_SERVER) \
		  -I$(DIR_CONFIG)
		  
LDFLAGS = -lpthread -lc -lgcc
LDFLAGS += -L$(DIR_LIB) \
			-lcommonfunc

CFLAGS := $(INCLUDE) -Wall -c -O2

CC=/opt/arm-toolchain/gcc-linaro-7.3.1-2018.05-i686_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-g++
STRIP=/opt/arm-toolchain/gcc-linaro-7.3.1-2018.05-i686_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-strip

VPATH = %.cpp $(DIR_COMMON) $(DIR_SERVER) $(DIR_CONFIG)

SRC=$(wildcard *.cpp ./*.cpp)
SRC+=$(wildcard *.cpp $(DIR_COMMON)/*.cpp)
SRC+=$(wildcard *.cpp $(DIR_SERVER)/*.cpp)
SRC+=$(wildcard *.cpp $(DIR_CONFIG)/*.cpp)

#输出段定义
TARGET = personal-cloud

DIR=$(notdir $(SRC))
OBJ=$(patsubst %.cpp,%.o,$(DIR))

all:$(TARGET)

$(TARGET):$(OBJ)
	$(CC) $^ -o $@ $(LDFLAGS) -static
	rm *.o

%.o: %.cpp
	$(CC) $(CFLAGS) $< -o $@


.PHONY: clean cleanobj
cleanobj:
	rm  -f $(OBJ)
clean:
	rm  -f $(OBJ) $(TARGET)

