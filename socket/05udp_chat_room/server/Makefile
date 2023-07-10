.PHONY:clean
CC:=gcc
TARGET:=server
OBJECT:=udp_server.o linklist.o
LIBS:=-lpthread

$(TARGET):$(OBJECT)
	$(CC) $^ $(LIBS) -o $@
$(OBJECT):%.o:%.c
	$(CC) -c $(LIBS) $^ -o $@

clean:
	rm -rf *.o server