.PHONY:clean
CC:=gcc
TARGET:=TARGET
SER_OBJECT:=server
CLI_OBJECT:=client

$(TARGET):$(SER_OBJECT) $(CLI_OBJECT)
$(CLI_OBJECT):
	$(CC) 01bind.c -o $@
$(SER_OBJECT):
	$(CC) 02listen_accept.c -o $@
clean:
	rm $(SER_OBJECT) $(CLI_OBJECT) -rf