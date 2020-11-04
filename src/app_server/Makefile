.SUFFIXES : .x .o .c .s

DIR_INC = ../includes
DIR_LIB = ../libs
DIR_LIB_INC = $(DIR_LIB)/inc
DIR_COMMON = ../app_server
DIR_SERVER = ../server
DIR_CONFIG = ../config
DIR_SHM= ../share_mem

INCLUDE = -I./ \
		  -I$(DIR_INC) \
		  -I$(DIR_LIB_INC) \
		  -I$(DIR_COMMON) \
		  -I$(DIR_SERVER) \
		  -I$(DIR_CONFIG) \
		  -I$(DIR_SHM)

LDFLAGS = -lc -lgcc
LDFLAGS += -L$(DIR_LIB) \
			-lcommonfunc \
			-lsqlite3 \
			-lpthread \
			-ldl

CFLAGS := $(INCLUDE) -Wall -c -O2

CC=/opt/arm-toolchain/gcc-linaro-7.3.1-2018.05-i686_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-g++
STRIP=/opt/arm-toolchain/gcc-linaro-7.3.1-2018.05-i686_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-strip

VPATH = %.cpp $(DIR_COMMON) $(DIR_SERVER) $(DIR_CONFIG) $(DIR_SHM)

SRC=$(wildcard *.cpp ./*.cpp)
SRC+=$(wildcard *.cpp $(DIR_COMMON)/*.cpp)
SRC+=$(wildcard *.cpp $(DIR_SERVER)/*.cpp)
SRC+=$(wildcard *.cpp $(DIR_CONFIG)/*.cpp)
SRC+=$(wildcard *.cpp $(DIR_SHM)/*.cpp)

#输出段定义
TARGET = cloud-server

DIR=$(notdir $(SRC))
OBJ=$(patsubst %.cpp,%.o,$(DIR))

all:$(TARGET)

$(TARGET):$(OBJ)
	$(CC) $^ -o $@ $(LDFLAGS)
	rm *.o

%.o: %.cpp
	$(CC) $(CFLAGS) $< -o $@


.PHONY: clean cleanobj
cleanobj:
	rm  -f $(OBJ)
clean:
	rm  -f $(OBJ) $(TARGET)

