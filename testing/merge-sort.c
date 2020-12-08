#include <stdio.h>
#include <stdlib.h>
#include "../ADTs/avl.h"
#include "../ADTs/bst.h"
#include "../Util/util.h"

#define SIZE 10

int main(){
    item *array = (item *)malloc(SIZE * sizeof(item));

    array[0] = (item) {"01", 1};
    array[1] = (item) {"02", 2};
    array[2] = (item) {"03", 3};
    array[3] = (item) {"04", 4};
    array[4] = (item) {"05", 5};
    array[5] = (item) {"06", 6};
    array[6] = (item) {"07", 7};
    array[7] = (item) {"08", 8};
    array[8] = (item) {"09", 9};
    array[9] = (item) {"10", 10};

    printf("\nnot sorted: \n");
    for(int i = 0; i < SIZE; i++){ printf("%s %d\n", array[i].string, array[i].occurrences); }
    sort(array, SIZE);
    printf("\nsorted: \n");
    for(int i = 0; i < SIZE; i++){ printf("%s %d\n", array[i].string, array[i].occurrences); }

    free(array);

    return 0;
}