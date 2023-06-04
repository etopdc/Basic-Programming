CC:=gcc
INCLUDE_DIR := -I .
TARGET:=a.out


$(TARGET):*.c
	@gcc $(INCLUDE_DIR) $^ -o $@

clean:
	@rm -rf a.out