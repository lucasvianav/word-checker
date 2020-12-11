/*
    Daniel Carvalho Dantas 10685702
    Lucas Viana Vilela 10748409
*/

#include <stdio.h>
#include <stdlib.h>
#include "ADTs/bst.h"
#include "ADTs/avl.h"
#include "Util/util.h"

int getNewDictIndex(avl **dicts){
    if(dicts != NULL){ for(int i = 0; i < MAX_DICTIONARIES; i++){ if(dicts[i] == NULL){ return i; } } }
    return Error;
}

int main(){
    int index; // Dict's index (id - 1)
    int operation; // Operation to be executed
    
    // Auxiliar variables in order to read
    // and dynamically allocate words
    char aux;
    char *word;
    int wordLength;

    // Array containing MAX_DICTIONARIES (3) AVLs (dictionaries)
    avl **dicts = (avl **)malloc(MAX_DICTIONARIES * sizeof(avl *));
    for(int i = 0; i < MAX_DICTIONARIES; i++){ dicts[i] = NULL; }

    // Infinite loop in which the program is executed
    while(1){
        // Reads the operation
        scanf("%d", &operation);

        // Executes different actions depending
        // on the received operation
        switch(operation){
            case 1: // Create a new dict (if possible) with the first avaliable index
                index = getNewDictIndex(dicts);

                // If the maximum amount of dicts was met
                if(index == Error){ printf("IMPOSSIVEL CRIAR\n"); }

                else{
                    dicts[index] = avl_new(); // Creates a new dict
                    
                    // Reads all of the new dict's words (input) and adds them to it
                    while(1){
                        // Reads a word (string)
                        readWord(&aux, &word, &wordLength);

                        // If the string is valid (a word instead of "\0"), adds  it to the dict
                        if(wordLength > 1){ avl_insert(dicts[index], word); }

                        // Frees the word
                        free(word);
                        
                        // If the input is finished
                        if(aux == '#'){ break; }
                    }

                    printf("DICIONARIO %d CRIADO\n", index+1);
                }

                break;

            case 2: // Updates a dict
                scanf("%d", &index); index--; // Reads the target-dict's id and sets the index (id - 1)

                // If the target-dict doesn't exist
                if(dicts[index] == NULL){ printf("DICIONARIO %d INEXISTENTE\n", index+1); }

                else{
                    // Reads and executes all of the updates
                    while(1){
                        int op; // Update operation (insertion x removal)

                        // Reads the operation
                        scanf("%d", &op);

                        // Reads the word (string) to be updated
                        readWord(&aux, &word, &wordLength);

                        // If the string is valid (a word instead of "\0")
                        if(wordLength > 1){
                            if(op == 0){ // Removal
                                // Tries to remove the passed word from the dict
                                // and prints the output accordingly
                                avl_remove(dicts[index], word) == Success 
                                    ? printf("%s EXCLUIDA DE %d\n", word, index + 1) 
                                    : printf("%s INEXISTENTE EM %d\n", word, index + 1);
                            }

                            else if(op == 1){ // Insertion
                                // Tries to insert the passed word to the dict
                                // and prints the output accordingly
                                avl_insert(dicts[index], word) == Success
                                    ? printf("%s INSERIDA EM %d\n",word,index + 1)
                                    : printf("%s JA EXISTE EM %d\n",word,index + 1);
                            }
                        }
                        
                        // Frees the word
                        free(word);
                        
                        // If the input is finished
                        if(aux == '#'){ break; }
                    }
                }

                break;

            case 3: // Deletes a dict
                scanf("%d", &index); index--; // Reads the target-dict's id and sets the index (id - 1)

                // Tries to delete the selected dict and
                // prints the output accordingly
                avl_delete(&(dicts[index])) == Success
                    ? printf("DICIONARIO %d APAGADO\n", index+1)
                    : printf("DICIONARIO %d INEXISTENTE\n", index+1);

                break;

            case 4: ;// Checks an input text agaisnt a dict
                int n; // Number of words from (input ∩ dict) to be printed

                // Reads the target-dict's id and sets the index (id - 1)
                scanf("%d %d", &index, &n); index--; 

                // If the selected dict doesn't exist
                if(dicts[index] == NULL){ printf("DICIONÁRIO INEXISTENTE\n"); }

                // If n is invalid
                else if(n <= 0){ printf("IMPOSSIVEL INFORMAR %d PALAVRAS MAIS FREQUENTES\n", n); }

                else{
                    // Binary search tree in which the input
                    // text's words will be stored (one per element)
                    bst *input = bst_new();

                    // Loop to read  the whole input text and
                    // insert each of it's words to the BST
                    while(1){
                        // Reads a word (string)
                        readWord(&aux, &word, &wordLength);

                        // If the string is valid (a word instead of "\0")
                        if(wordLength > 1){ bst_insert(input, word); }

                        // Frees the word
                        free(word);

                        // If the input is finished
                        if(aux == '#'){ break; }
                    }

                    // Number of words from the input that are also in the dict
                    int intersectionSize;

                    // "input ∩ dict": intersection between the input and the dict
                    // (i.e.: words from the input that are also in the dict)
                    item *intersection = bst_popAvlIntersection(input, dicts[index], &intersectionSize);
                    // (intersection words are removed from the input BST)

                    // Merge sorts the intersection array by number of occurrences
                    // (it's a stablesort, so the alphabetical order is maintained)
                    sort(intersection, intersectionSize);

                    // Prints all the input word's that weren't also in the dict
                    bst_print(input);

                    // Prints the intersection and frees it's strings
                    for(int i = 0; i < intersectionSize && i < n; i++){ 
                        printf("%s %d\n", intersection[i].string, intersection[i].occurrences);
                        free(intersection[i].string);
                    }

                    // Frees allocated memory
                    bst_delete(&input);
                    free(intersection);
                }

                break;

            case 0: // Ends the program's execution
                // Frees all allocated memory
                for(int i = 0; i < MAX_DICTIONARIES; i++){ avl_delete(&(dicts[i])); }
                free(dicts);

                return 0;

            default: // If no valid operation was passed, do nothing
                break;
        }
    }

    return 0;
}