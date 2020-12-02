/*
    Daniel Carvalho Dantas 10685702
    Lucas Viana Vilela 10748409
*/

#ifndef BST_H
#define BST_H

#include "../Util/util.h"
#include "./avl.h"

typedef struct bst_ bst; // Binary Search Tree

// Retorna o ponteiro para a BST criada
bst *bst_new();

// Recebe o endereço do ponteiro para a BST a ser excluída
// Retorna 1 se a exclusão for bem sucedida ou Error caso contrário
int bst_delete(bst **t);

// Recebe o item a ser inserido e o ponteiro para a BST
// Retorna 1 se a inserção for bem-sucedida ou Error caso contrário
int bst_insert(bst *t, char *word);

// Recebe a chave do item a ser removido e o ponteiro para a BST
// Retorna 1 se a inserção for bem-sucedida ou Error caso contraŕio
int bst_remove(bst *t, char *key);

// Recebe o ponteiro para a BST
// Retorna a altura da BST ou Error caso ela não exista
int bst_getHeight(bst *t);

// Recebe a chave do item a ser buscado e o ponteiro para a BST
// Retorna o título do item encontrado ou Error caso ele não seja
// encontrado
item bst_search(bst *t, char *key);

// Recebem o ponteiro para a BST
// Printa todos os itens da BST em ordem
void bst_print(bst *t);

// Recebe uma bst, uma avl e um inteiro (por referência) que vai representar
// o tamanho do array que retorna
// vai percorrer a bst em ordem e checar se cada elemento está contido na avl.
// todos os elementos que estiverem contidos na avl, serão removidos da bst
// e armazenados em um array de item, que será retornado pela função
item *bst_popAvlIntersection(bst *BST, avl *AVL, int *arraySize);

#endif