/*
    Daniel Carvalho Dantas 10685702
    Lucas Viana Vilela 10748409
*/
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

void remove_hashtag(char* input){

    int i = 0;

    while(input[i]!= '#'){
        i++;
    }

    input[i] = '\0';

}
