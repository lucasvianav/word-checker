/*
    Daniel Carvalho Dantas 10685702
    Lucas Viana Vilela 10748409
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"
#include "utils.h"

#define MAX_INPUT_SIZE 800

int main(){

    int i;
    int n_frequent_words,current_dictionary;
    int operation = 1;
    int num_dictionaries = 0;

    // Allocates an array of 3 dictionaries
    bst** dictionaries;
    dictionaries = (bst**)malloc(3 * sizeof(bst*));

    for(i = 0; i < 3; i++){
        dictionaries[i] = (bst*)malloc(sizeof(bst));
    }


    while(operation != 0){

        scanf("%d",&operation);

        switch(operation){

            // Exit
            case 0:
            break;

            // Create
            case 1:
            break;

            // Update
            case 2:
            break;

            // Delete
            case 3:
            break;

            // Verify
            case 4:

            scanf("%d %d",&current_dictionary,&n_frequent_words);
            
            char* input;
            fgets(input,MAX_INPUT_SIZE,stdin);

            break;

            default:
            break;


        }
    }

    // Deallocates the dictionaries
    for(i = 0; i < 3; i++){
        free(dictionaries[i]);
    }

    free(dictionaries);

    return 0;
}