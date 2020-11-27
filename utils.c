/*
    Daniel Carvalho Dantas 10685702
    Lucas Viana Vilela 10748409
*/
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "abb.h"

void remove_hashtag(char* input){

    int i = 0;

    while(input[i]!= '#'){
        i++;
    }

    input[i] = '\0';

}

int find_new_id(bst** trees){

    if(trees == NULL){
        return -32000;
    }

    int i;

    for(i = 0; i < 3; i++){
        
        if(bst[i] == NULL){
            return i;
        }

    }
}
