bstVector-main:
	gcc -g3 -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer -Werror -Wall -std=c99 bst-vector.c ../ADTs/bst.c ../ADTs/bst.h ../Util/util.c ../Util/util.h -o bst-vector
bstVector-run:
	./bst-vector
avl-main:
	gcc -g3 -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer -Werror -Wall -std=c99 avl.c ../ADTs/avl.c ../ADTs/avl.h ../Util/util.c ../Util/util.h -o avl
avl-run:
	./avl
avlBst-main:
	gcc -g3 -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer -Werror -Wall -std=c99 avl-bst.c ../ADTs/bst.c ../ADTs/bst.h ../ADTs/avl.c ../ADTs/avl.h ../Util/util.c ../Util/util.h -o avl-bst
avlBst-run:
	./avl-bst
treeInsertion-main:
	gcc -g3 -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer -Werror -Wall -std=c99 tree-insertion.c ../ADTs/avl.c ../ADTs/avl.h ../ADTs/bst.c ../ADTs/bst.h ../Util/util.c ../Util/util.h -o tree-insertion
treeInsertion-run:
	./tree-insertion