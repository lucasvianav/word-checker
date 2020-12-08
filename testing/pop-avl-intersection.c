#include <stdio.h>
#include <stdlib.h>
#include "../ADTs/avl.h"
#include "../ADTs/bst.h"
#include "../Util/util.h"

int main(){
    avl *AVL = avl_new();
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

    avl_insert(AVL, "08"); 
    avl_insert(AVL, "02"); 
    avl_insert(AVL, "01"); 
    avl_insert(AVL, "05"); 
    avl_insert(AVL, "07"); 

    printf("\navl: \n");
    avl_print(AVL);

    printf("\nbst: \n");
    bst_print(BST);
    printf("\n\n");

    int size;
    item *intersection = bst_popAvlIntersection(BST, AVL, &size);

    printf("\nnot sorted: \n");
    for(int i = 0; i < size; i++){ printf("%s %d\n", intersection[i].string, intersection[i].occurrences); }
    sort(intersection, size);
    printf("\nsorted: \n");
    for(int i = 0; i < size; i++){ printf("%s %d\n", intersection[i].string, intersection[i].occurrences); }

    avl_delete(&AVL);
    bst_delete(&BST);
    for(int i = 0; i < size; i++){ free(intersection[i].string); }

    return 0;
}