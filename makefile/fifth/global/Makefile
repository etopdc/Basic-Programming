SRC=$(wildcard *.c)

OBJ=$(patsubst %c, %o, $(SRC))

all:$(OBJ)

$(OBJ):%.o:%.c
	$(CC) $(INCLUDE_DIR) -c $^ -o $(OBJ_DIR)/$@