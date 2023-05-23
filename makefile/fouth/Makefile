SUB_DIR := main fun global obj
export SUB_DIR

all:$(SUB_DIR)

$(SUB_DIR):MK_BIN
	make -C $@

MK_BIN:
	mkdir -p ./bin

clean:
	rm -rf obj/*.o bin

