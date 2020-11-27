#ifndef ABB_H
#define ABB_H

#define Error -32000
#define ErrorStr "-32000" // código de erro em forma de string

typedef struct bst_ bst; // Binary Search Tree

typedef struct item_ {
    int key;
    char title[20];
} item;

// Retorna o ponteiro para a BST criada
bst *bst_new();

// Recebe o endereço do ponteiro para a BST a ser excluída
// Retorna 1 se a exclusão for bem sucedida ou Error caso contrário
int bst_delete(bst **t);

// Recebe o item a ser inserido e o ponteiro para a BST
// Retorna 1 se a inserção for bem-sucedida ou Error caso contrário
int bst_insert(bst *t, item movie);

// Recebe a chave do item a ser removido e o ponteiro para a BST
// Retorna 1 se a inserção for bem-sucedida ou Error caso contraŕio
int bst_remove(bst *t, int key);

// Recebe o ponteiro para a BST
// Retorna a altura da BST ou Error caso ela não exista
int bst_getHeight(bst *t);

// Recebe a chave do item a ser buscado e o ponteiro para a BST
// Retorna o título do item encontrado ou Error caso ele não seja
// encontrado
char *bst_search(bst *t, int key);

// Recebem o ponteiro para a BST
// Printa todos os itens da BST em ordem
void bst_print(bst *t);

#endif