/*
    Daniel Carvalho Dantas 10685702
    Lucas Viana Vilela 10748409
*/

#ifndef BST_H
#define BST_H

#include "../Util/util.h"

typedef struct bst_ bst; // Binary Search Tree

// Retorna o ponteiro para a BST criada
bst *bst_new();

// Recebe o endereço do ponteiro para a BST a ser excluída
// Retorna 1 se a exclusão for bem sucedida ou Error caso contrário
int bst_delete(bst **t);

// Recebe o item a ser inserido e o ponteiro para a BST
// Retorna 1 se a inserção for bem-sucedida ou Error caso contrário
int bst_insert(bst *t, item word);

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

// Aloca os 3 dicionários necessários para a main
bst** allocate_dictionaires();

// Verifica se ainda é possível criar um dicionário
// Se sim, retorna o id
int get_new_dict_id(bst **dictionaries);

#endif