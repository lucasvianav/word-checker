#include <stdio.h>
#include "../ADTs/avl.h"

int main(){
    avl *tree = avl_new();

    // avl_insert(tree, "a");
    // avl_insert(tree, "b");
    // avl_insert(tree, "c");
    // avl_insert(tree, "d");
    // avl_insert(tree, "e");
    // avl_insert(tree, "f");
    // avl_insert(tree, "g");
    // avl_insert(tree, "h");
    // avl_insert(tree, "i");

    // avl_remove(tree, "a");
    // avl_remove(tree, "b");



    // avl_insert(tree, "08");
    // avl_insert(tree, "04");
    // avl_insert(tree, "10");
    // avl_insert(tree, "02");
    // avl_insert(tree, "06");
    // avl_insert(tree, "05");



    avl_insert(tree, "11");
    avl_insert(tree, "09");
    avl_insert(tree, "14");
    avl_insert(tree, "10");
    avl_insert(tree, "12");
    avl_insert(tree, "15");
    avl_insert(tree, "13");
    avl_insert(tree, "19");

    avl_remove(tree, "19");
    avl_remove(tree, "10");
    avl_remove(tree, "14");

    avl_print(tree);

    avl_delete(&tree);

    return 0;
}