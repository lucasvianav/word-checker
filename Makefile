all:
	gcc -Wall -std=c99 main.c ADTs/bst.c utils.c -o main 
run:
	./main