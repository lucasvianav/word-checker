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

#define MAX_DICTIONARIES 3

typedef struct item_ {
    char *string;
    int occurrences;
} item;

// Remove a # do final do input
void remove_hashtag(char* string);

// Insere as palavras em um novo dicionário
//void insert_words(bst* dictionary);
 
#endif