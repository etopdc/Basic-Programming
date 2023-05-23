main_exec : main.o head.o 
	gcc main.o head.o -o main_exec

main.o : main.c 
	gcc -c main.c -o main.o 

head.o : head.c 
	gcc -c head.c -o head.o

clean :
	rm -rf *.o main_exec