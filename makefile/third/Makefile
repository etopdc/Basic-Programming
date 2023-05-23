# $@ 目标集合
# $^ 依赖集合
# $< 第一个依赖

CC = gcc
TARGET = all
OBJECT = main.o head.o

${TARGET}:${OBJECT}
	${CC} $^ -o ${TARGET}

%.o:%.c
	${CC} -c $< -o $@

clean :
	rm -rf *.o ${TARGET}