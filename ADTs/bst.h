/*
    Daniel Carvalho Dantas 10685702
    Lucas Viana Vilela 10748409
*/

#ifndef BST_H
#define BST_H

#include "../Util/util.h"
#include "./avl.h"

typedef struct bst_ bst; // Binary Search Tree

// Returns a pointer to the created BST
bst *bst_new();

// Receives the pointer to the target-BST's address
// If the deletion was successful, returns Success, else Error
// (if the BST doesn't exit - i.e. is NULL - returns Error)
int bst_delete(bst **t);

// Receives the word to be inserted and the pointer to the target-BST
// If the insertion was successful, returns Success, else Error
// (if the BST already contains that word, increments it's occurrence
// and returns Success)
// The BST is in alphabetical order
int bst_insert(bst *t, char *word);

// Receives word (key) to be removed and the pointer to the target-BST
// If the removal was successful, returns Success, else Error
int bst_remove(bst *t, char *key);

// Receives the pointer to the target-BST
// If the BST exists, eturns the it's height, else Error
int bst_getHeight(bst *t);

// Receives the word (key) to be searched and the pointer
// to the target-AVl
// If the word is found, returns it's item, else ErrorItem
item bst_search(bst *t, char *key);

// Receives the pointer to the target-BST
// Prints all of the BST's words in-order
void bst_print(bst *t);

// Receives the pointer to the target-BST and the target-AVL, as well as 
// a pointer to an int which represents the intersection's size (number of
// elements in it's array)
// Goes through the BST in-order and checks each element agaisnt the AVL
// When it finds an element in the BST that's also in the AVL, pulls it from
// the BST and inserts it into an array of items
// Returns the built array of items (intersection between the BST and the AVL)
item *bst_popAvlIntersection(bst *BST, avl *AVL, int *arraySize);

#endif