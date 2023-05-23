CC := gcc
INCLUDE_DIR := -I ../include

SUB_DIR := main fun global obj
OBJ_DIR := ${shell pwd}/obj
BIN_DIR := ${shell pwd}/bin

TARGET := my_exec

export CC INCLUDE_DIR SUB_DIR OBJ_DIR BIN_DIR TARGET

all:$(SUB_DIR)

$(SUB_DIR):MK_BIN
	make -C $@

MK_BIN:
	mkdir -p $(BIN_DIR)

clean:
	rm -rf obj/*.o bin

