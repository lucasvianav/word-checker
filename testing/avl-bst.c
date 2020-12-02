#include <stdio.h>
#include "../ADTs/avl.h"
#include "../ADTs/bst.h"
#include "../Util/util.h"

int main(){
    avl *tree = avl_new();
    bst *bin = bst_new();

    avl_insert(tree, "11");
    avl_insert(tree, "09");
    avl_insert(tree, "14");
    avl_insert(tree, "10");
    avl_insert(tree, "12");
    avl_insert(tree, "15");
    avl_insert(tree, "13");
    avl_insert(tree, "19");

    bst_insert(bin, (item) {"11", 1});
    bst_insert(bin, (item) {"09", 1});
    bst_insert(bin, (item) {"14", 1});
    bst_insert(bin, (item) {"10", 1});
    bst_insert(bin, (item) {"12", 1});
    bst_insert(bin, (item) {"15", 1});
    bst_insert(bin, (item) {"13", 1});
    bst_insert(bin, (item) {"19", 1});

    avl_print(tree);
    bst_print(bin);

    avl_delete(&tree);
    bst_delete(&bin);

    return 0;
}