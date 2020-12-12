/*
    Daniel Carvalho Dantas 10685702
    Lucas Viana Vilela 10748409
*/

#ifndef UTILS_H
#define UTILS_H

#define Success 1
#define Error -32000
#define ErrorStr "-32000"
#define ErrorItem (item) {ErrorStr, Error}

// Maximum number of simultaneous dictionaries
#define MAX_DICTIONARIES 3

typedef struct item_ {
    char *string; // word
    int occurrences; // number of times the word appears in a text
} item;

// Reads a word from stdin
void readWord(char *aux, char **word, int *wordLength);

// Merge sorts the vector by item.occurrences (higher to lower)
void sort(item *vector, int vectorSize);
 
#endif