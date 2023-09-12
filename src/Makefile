all : stack_str main
	gcc main.o stack_str.o -o test

stack_str :
	gcc -c stack_str.c -Wextra -Wall -o stack_str.o

main :
	gcc -c main.c -Wextra -Wall -o main.o

clean :
	rm *.o
	rm test
