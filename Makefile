# Makefile

CC=g++
CPP=g++
AR=ar crD

CFLAGS = -Wall -std=c++11

RFLAGS=-O3 $(CFLAGS)
DFLAGS=-g $(CFLAGS)

SOURCE_DIR=.

RELEASE_DIR=RELEASE
DEBUG_DIR=DEBUG

TARGET=libxlog.a

RELEASE_TARGET=$(RELEASE_DIR)/$(TARGET)
DEBUG_TARGET=$(DEBUG_DIR)/$(TARGET)

CFILE=$(foreach dir, $(SOURCE_DIR), $(wildcard $(dir)/*.c))
CPPFILE=$(foreach dir, $(SOURCE_DIR), $(wildcard $(dir)/*.cpp))

COBJS=$(patsubst %.c,%.o, $(CFILE))
CPPOBJS=$(patsubst %.cpp,%.o, $(CPPFILE))

all:output

.PHONY:clean

release:$(RELEASE_DIR)/. $(RELEASE_TARGET)
debug:$(DEBUG_DIR)/. $(DEBUG_TARGET)
output:release
	cp $(RELEASE_TARGET) output/lib/
	cp xlog.h output/include/

%/.:
	mkdir -p $*

$(DEBUG_DIR)/%.o:%.c
	$(CC) $(DFLAGS) -c $^ -o $@

$(DEBUG_DIR)/%.o: %.cpp
	$(CPP) $(DFLAGS) -c $< -o $@

$(DEBUG_TARGET):$(addprefix $(DEBUG_DIR)/,$(COBJS)) $(addprefix $(DEBUG_DIR)/,$(CPPOBJS))
	$(AR) $@ $^ 

$(RELEASE_DIR)/%.o:%.c
	$(CC) $(RFLAGS) -c $^ -o $@

$(RELEASE_DIR)/%.o: %.cpp
	$(CPP) $(RFLAGS) -c $< -o $@

$(RELEASE_TARGET):$(addprefix $(RELEASE_DIR)/,$(COBJS)) $(addprefix $(RELEASE_DIR)/,$(CPPOBJS))
	$(AR) $@ $^ 

clean:
	rm -rf $(RELEASE_DIR) $(DEBUG_DIR)
