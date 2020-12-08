/*
    Daniel Carvalho Dantas 10685702
    Lucas Viana Vilela 10748409
*/

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "util.h"
#include "../ADTs/bst.h"

void remove_hashtag(char *string){
    int i = 0;
    while(string[i] != '#'){ i++; }
    string[i] = '\0';

    return;
}


// Receives a vector and the position of two sorted subvectors inside it - merges both of them into a fully sorted one
void mergeSubvectors(item *vector, int firstLeftIndex, int firstRightIndex, int secondLeftIndex, int secondRightIndex){
    int vectorSize = (firstRightIndex - firstLeftIndex + 1) + (secondRightIndex - secondLeftIndex + 1);

    item *tmp = (item*)malloc(vectorSize * sizeof(item)); // Temporary vector in which the interpolation will occur
    
    int i, j, k = 0; // Auxiliar variables that'll index the for-loops

    // Loops through both subvectors, merging them
    for(i = firstLeftIndex, j = secondLeftIndex; k < vectorSize; k++){

        // If there are still elements in both subvector
        if(i <= firstRightIndex && j <= secondRightIndex){ 
            // Compares them and copies the lowest one to tmp
            if(vector[i].occurrences > vector[j].occurrences){ tmp[k] = vector[i++]; }
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
        int middleIndex = (rightIndex + leftIndex) / 2;

        mergeSort(vector, leftIndex, middleIndex);
        mergeSort(vector, middleIndex + 1, rightIndex);
        mergeSubvectors(vector, leftIndex, middleIndex, middleIndex + 1, rightIndex);
    }

    return;
}

void sort(item *vector, int vectorSize){
    return mergeSort(vector, 0, vectorSize-1);
}