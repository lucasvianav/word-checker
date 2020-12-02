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

    bst_insert(bin, "11");
    bst_insert(bin, "09");
    bst_insert(bin, "14");
    bst_insert(bin, "10");
    bst_insert(bin, "12");
    bst_insert(bin, "15");
    bst_insert(bin, "13");
    bst_insert(bin, "19");

    avl_print(tree);
    bst_print(bin);

    avl_delete(&tree);
    bst_delete(&bin);

    return 0;
}