#include <stdio.h>
#include <stdlib.h>
#include "../ADTs/bst.h"
#include "../Util/util.h"

int main(){
    bst **dicts = (bst **)malloc(MAX_DICTIONARIES * sizeof(bst *));
    if(dicts != NULL){
        printf("vetor alocado\n");

        for(int i = 0; i < MAX_DICTIONARIES; i++){ 
            dicts[i] = bst_new(); 
            if(dicts[i] != NULL){ printf("árvore na posição %d do vetor alocada\n", i); }
        }

        for(int i = 0; i < MAX_DICTIONARIES; i++){
            item it = {"palavra", i};
            printf("inserção: %d\n", bst_insert(dicts[i], it));
            bst_print(dicts[i]);
            printf("exclusão: %d\n", bst_delete(&(dicts[i])));
        }

        free(dicts);
    }

    return 0;
}