#include <stdio.h>
#include <stdlib.h>
#include "../ADTs/avl.h"
#include "../ADTs/bst.h"
#include "../Util/util.h"

int main(){
    avl *dict = avl_new();
    bst *input = bst_new();

    avl_insert(dict, "soldiers");
    avl_insert(dict, "smiling");
    avl_insert(dict, "shaped");
    avl_insert(dict, "hearts");
    avl_insert(dict, "gardeners");
    avl_insert(dict, "king");
    avl_insert(dict, "queen");
    avl_insert(dict, "velvet");
    avl_insert(dict, "diamonds");
    avl_insert(dict, "clubs");

    bst_insert(input, "first");
    bst_insert(input, "came");
    bst_insert(input, "ten");
    bst_insert(input, "soldiers");
    bst_insert(input, "carrying");
    bst_insert(input, "clubs");
    bst_insert(input, "these");
    bst_insert(input, "were");
    bst_insert(input, "all");
    bst_insert(input, "shaped");
    bst_insert(input, "like");
    bst_insert(input, "the");
    bst_insert(input, "three");
    bst_insert(input, "gardeners");
    bst_insert(input, "oblong");
    bst_insert(input, "and");
    bst_insert(input, "flat");
    bst_insert(input, "with");
    bst_insert(input, "their");
    bst_insert(input, "hands");
    bst_insert(input, "and");
    bst_insert(input, "feet");
    bst_insert(input, "at");
    bst_insert(input, "the");
    bst_insert(input, "corners");
    bst_insert(input, "next");
    bst_insert(input, "the");
    bst_insert(input, "ten");
    bst_insert(input, "courtiers");
    bst_insert(input, "these");
    bst_insert(input, "were");
    bst_insert(input, "ornamented");
    bst_insert(input, "all");
    bst_insert(input, "over");
    bst_insert(input, "with");
    bst_insert(input, "diamonds");
    bst_insert(input, "and");
    bst_insert(input, "walked");
    bst_insert(input, "two");
    bst_insert(input, "and");
    bst_insert(input, "two");
    bst_insert(input, "as");
    bst_insert(input, "the");
    bst_insert(input, "soldiers");
    bst_insert(input, "did");

    printf("\ndict: \n");
    avl_print(dict);

    printf("\ninput: \n");
    bst_print(input);
    printf("\n\n");

    int size;
    item *intersection = bst_popAvlIntersection(input, dict, &size);

    printf("\nintersection: \n");
    printf("not sorted: \n");
    for(int i = 0; i < size; i++){ printf("%s %d\n", intersection[i].string, intersection[i].occurrences); }
    sort(intersection, size);
    printf("\nsorted: \n");
    for(int i = 0; i < size; i++){ printf("%s %d\n", intersection[i].string, intersection[i].occurrences); }

    printf("\ndict: \n");
    avl_print(dict);

    printf("\ninput: \n");
    bst_print(input);
    printf("\n\n");

    avl_delete(&dict);
    bst_delete(&input);
    for(int i = 0; i < size; i++){ free(intersection[i].string); }
    free(intersection);
    
    return 0;
}