all : stack_str main parse_tree
	gcc main.o stack_str.o parse_tree.o -o test

stack_str :
	gcc -c stack_str.c -Wextra -Wall -o stack_str.o

parse_tree :
	gcc -c parse_tree.c -Wextra -Wall -o parse_tree.o

main :
	gcc -c main.c -Wextra -Wall -o main.o

clean :
	rm *.o
	rm test
