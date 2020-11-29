all:
	gcc -Wall -std=c99 main.c ADTs/bst.c ADTs/bst.h Util/util.c Util/util.h -o main
mem:
	gcc -g3 -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer -Werror -Wall -std=c99 main.c ADTs/bst.c ADTs/bst.h Util/util.c Util/util.h -o main
run:
	./main