/*
    Daniel Carvalho Dantas 10685702
    Lucas Viana Vilela 10748409
*/

#ifndef AVL_H
#define AVL_H

#include "../Util/util.h"

typedef struct avl_ avl; // Binary Search Tree

// Retorna o ponteiro para a AVL criada
avl *avl_new();

// Recebe o endereço do ponteiro para a AVL a ser excluída
// Retorna 1 se a exclusão for bem sucedida ou Error caso contrário
int avl_delete(avl **t);

// Recebe o char *a ser inserido e o ponteiro para a AVL
// Retorna 1 se a inserção for bem-sucedida ou Error caso contrário
int avl_insert(avl *t, char *word);

// Recebe a chave do char *a ser removido e o ponteiro para a AVL
// Retorna 1 se a inserção for bem-sucedida ou Error caso contraŕio
int avl_remove(avl *t, char *key);

// Recebe o ponteiro para a AVL
// Retorna a altura da AVL ou Error caso ela não exista
int avl_getHeight(avl *t);

// Recebe a chave do char *a ser buscado e o ponteiro para a AVL
// Retorna o título do char *encontrado ou Error caso ele não seja
// encontrado
int avl_search(avl *t, char *key);

// Recebem o ponteiro para a AVL
// Printa todos os itens da AVL em ordem
void avl_print(avl *t);

#endif