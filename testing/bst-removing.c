#include <stdio.h>
#include <stdlib.h>
#include "../ADTs/bst.h"
#include "../Util/util.h"

int main(){
    bst *BST = bst_new();

    bst_insert(BST, "01");
    bst_insert(BST, "02");
    bst_insert(BST, "02");
    bst_insert(BST, "03");
    bst_insert(BST, "03");
    bst_insert(BST, "03");
    bst_insert(BST, "04");
    bst_insert(BST, "04");
    bst_insert(BST, "04");
    bst_insert(BST, "04");
    bst_insert(BST, "05");
    bst_insert(BST, "05");
    bst_insert(BST, "05");
    bst_insert(BST, "05");
    bst_insert(BST, "05");
    bst_insert(BST, "06");
    bst_insert(BST, "06");
    bst_insert(BST, "06");
    bst_insert(BST, "06");
    bst_insert(BST, "06");
    bst_insert(BST, "06");
    bst_insert(BST, "07");
    bst_insert(BST, "07");
    bst_insert(BST, "07");
    bst_insert(BST, "07");
    bst_insert(BST, "07");
    bst_insert(BST, "07");
    bst_insert(BST, "07");
    bst_insert(BST, "08");
    bst_insert(BST, "08");
    bst_insert(BST, "08");
    bst_insert(BST, "08");
    bst_insert(BST, "08");
    bst_insert(BST, "08");
    bst_insert(BST, "08");
    bst_insert(BST, "08");

    printf("\nbst: \n");
    bst_print(BST);
    printf("\n\n");

    bst_remove(BST, "06");

    printf("\nbst: \n");
    bst_print(BST);
    printf("\n\n");

    bst_delete(&BST);
    
    return 0;
}