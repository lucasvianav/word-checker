/*
    Daniel Carvalho Dantas 10685702
    Lucas Viana Vilela 10748409
*/

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "util.h"

// Receives a vector and the position of two sorted subvectors inside it - merges both of them into a fully sorted one
void mergeSubvectors(item *vector, int firstLeftIndex, int firstRightIndex, int secondLeftIndex, int secondRightIndex){
    int vectorSize = (firstRightIndex - firstLeftIndex + 1) + (secondRightIndex - secondLeftIndex + 1);

    item *tmp = (item*)malloc(vectorSize * sizeof(item)); // Temporary vector in which the interpolation will occur
    
    int i, j, k = 0; // Auxiliar variables that'll index the for-loops

    // Loops through both subvectors, merging them
    for(i = firstLeftIndex, j = secondLeftIndex; k < vectorSize; k++){

        // If there are still elements in both subvector
        if(i <= firstRightIndex && j <= secondRightIndex){ 
            // Compares them and copies the higher one to tmp
            if(vector[i].occurrences >= vector[j].occurrences){ tmp[k] = vector[i++]; }
            else{ tmp[k] = vector[j++]; }
        }

        // If not, copies the remaining element to tmp
        else if(i <= firstRightIndex){ tmp[k] = vector[i++]; }
        else if(j <= secondRightIndex){ tmp[k] = vector[j++]; }
    }

    // Copies the sorted vector in tmp to the original one, replacing the subvectors
    for(i = firstLeftIndex, j = secondLeftIndex, k = 0; k < vectorSize; k++){
        if(i <= firstRightIndex){ vector[i++] = tmp[k]; }
        else{ vector[j++] = tmp[k]; }
    }

    free(tmp); tmp = NULL;

    return;
}

// MERGE SORT
void mergeSort(item *vector, int leftIndex, int rightIndex){
    if(rightIndex > leftIndex){
        // Middle of the vector
        int middleIndex = (rightIndex + leftIndex) / 2;

        // Sorts the first half
        mergeSort(vector, leftIndex, middleIndex);
        // Sorts the second half
        mergeSort(vector, middleIndex + 1, rightIndex);
        // Merges both sorted halfs
        mergeSubvectors(vector, leftIndex, middleIndex, middleIndex + 1, rightIndex);
    }

    return;
}

void sort(item *vector, int vectorSize){
    // Merge sorts the whole vector
    return mergeSort(vector, 0, vectorSize-1);
}

void readWord(char *aux, char **word, int *wordLength){
    *wordLength = 0; // number of chars in the word ('\0' included)
    *word = (char *)malloc(sizeof(char)); // word

    // reads each of the word's letters
    while(1){
        // reads a cahr
        scanf("%c", aux);

        // reallocates the word so it'll fit the new char
        *word = (char *)realloc((*word), ++(*wordLength) * sizeof(char));

        // adds either the new char or '\0' (if it's invalid) to the word
        (*word)[*wordLength-1] = (*aux != '\n' && *aux != '\r' && *aux != '#' && *aux != ' ') ? *aux : '\0';

        // if '\0' was added to the word, then it's finished
        if(*aux == '\n' || *aux == '\r' || *aux == '#' || *aux == ' '){ return; }
    }

    return;
}