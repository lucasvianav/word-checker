#include <stdio.h>
#include <stdlib.h>
#include "../ADTs/avl.h"
#include "../ADTs/bst.h"

int main(){
    avl *dict_AVL = avl_new();
    bst *dict_BST = bst_new();

    int wordLength;
    char *word;
    char aux;
    
    while(1){
        wordLength = 0;
        word = (char *)malloc(sizeof(char));

        while(1){
            scanf("%c", &aux);

            word = (char *)realloc(word, ++wordLength * sizeof(char));
            word[wordLength-1] = (aux != '\n' && aux != '#' && aux != ' ') ? aux : '\0';

            if(aux == '\n' || aux == '#' || aux == ' '){ break; }
        }

        if(wordLength > 1){ 
            avl_insert(dict_AVL, word); 
            bst_insert(dict_BST, word); 
        }

        free(word);
        
        if(aux == '#'){ break; }
    }

    printf("\navl: \n");
    avl_print(dict_AVL);

    printf("\nbst: \n");
    bst_print(dict_BST);

    avl_delete(&dict_AVL);
    bst_delete(&dict_BST);

    return 0;
}