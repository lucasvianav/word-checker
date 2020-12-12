/*
    Daniel Carvalho Dantas 10685702
    Lucas Viana Vilela 10748409
*/

#ifndef AVL_H
#define AVL_H

#include "../Util/util.h"

typedef struct avl_ avl;

// Returns a pointer to the created AVL
avl *avl_new();

// Receives the pointer to the target-AVL's address
// If the deletion was successful, returns Success, else Error
// (if the AVL doesn't exit - i.e. is NULL - returns Error)
int avl_delete(avl **t);

// Receives the word to be inserted and the pointer to the target-AVL
// If the insertion was successful, returns Success, else Error
// (if the AVL already contains that word, returns Error)
// The AVL is in alphabetical order
int avl_insert(avl *t, char *word);

// Receives word (key) to be removed and the pointer to the target-AVL
// If the removal was successful, returns Success, else Error
int avl_remove(avl *t, char *key);

// Receives the pointer to the target-AVL
// If the AVL exists, eturns the it's height, else Error
int avl_getHeight(avl *t);

// Receives the word (key) to be searched and the pointer
// to the target-AVl
// If the word is found, returns it's node's height, else Error
int avl_search(avl *t, char *key);

// Receives the pointer to the target-AVL
// Prints all of the AVL's words in-order
void avl_print(avl *t);

#endif