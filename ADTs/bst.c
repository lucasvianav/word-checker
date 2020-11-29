/*
    Daniel Carvalho Dantas 10685702
    Lucas Viana Vilela 10748409
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./bst.h"

struct node_ {
    item word;
    struct node_ *left; // subárvore à esquerda do nó
    struct node_ *right; // subárvore à direita do nó
};
typedef struct node_ node;

struct bst_ {
    node *root;
};


bst *bst_new(){
    bst *tree = (bst *)malloc(sizeof(bst)); // aloca uma nova BST
    if(tree == NULL){ return NULL; } // verifica se a alocação foi bem-sucedida

    tree->root = NULL; // anula a raiz

    return tree;
}

// essa e todas as outras funções 'aux' (auxiliar) são internas
// desaloca todos os nós da subárvore com *current como raiz
void auxDelete(node **current){
    if(*current != NULL){ // garante que só vai percorrer os nós até encontrar uma folha
        auxDelete(&((*current)->left)); // recursivamente deleta a subárvore à esquerda desse nó
        auxDelete(&((*current)->right)); // ||              ||  ||    ||    ||  direita   ||  ||

        // após desalocar as subárvores esquerda e direita, faz o mesmo pra raiz
        // (percurso pós-ordem)

        free(*current); // desaloca o nó-raiz
        *current = NULL;
    }

    return;
}

int bst_delete(bst **t){
    if(*t == NULL){ return Error; } // verifica se a BST existe

    auxDelete(&((*t)->root)); // desaloca todos os nós da lista

    free(*t); // desaloca a árvore
    *t = NULL;

    return Success;
}

// função interna que insere o nó new na posição correta no interior
// da subárvore com raiz *current
// vai incrementar height para cada nível que descer na árvore
// no total, vai somar comprimento do percurso feito + 1 ao valor
// inicial de height
int auxInsert(node **current, node *new){
    if(*current == NULL){ // caso base --> a posição correta para o novo nó foi encontrada
        *current = new; // insere na posição
        return Success;
    }

    // caso contrário:

    // se a palavra do nó atual for igual ao do novo nó
    if(strcmp((*current)->word.string, new->word.string) == 0){ return Error; }

    // se a palavra do nó atual alfabeticamente viria depois da do novo nó
    else if(strcmp((*current)->word.string, new->word.string) > 0){
        return auxInsert(&((*current)->left), new); // recursivamente procura a posição para inserir na subárvore esquerda
    }

    // caso contrário, faz o mesmo pra subárvore direita
    else{ return auxInsert(&((*current)->right), new); }
}

int bst_insert(bst *t, item word){
    node *newNode = (node *)malloc(sizeof(node)); // aloca um novo nó

    // checa se a árvore existe e se a alocação
    // do novo nó foi bem-sucedida
    if(t == NULL || newNode == NULL){ 
        if(newNode != NULL){ free(newNode); }
        return Error; 
    }

    // ajusta as informações do novo nó
    newNode->word = word;
    newNode->left = NULL;
    newNode->right = NULL;

    // caso a árvore esteja vazia
    if(t->root == NULL){
        t->root = newNode; // insere o nó na raiz
        return Success;
    }

    // caso não esteja vazia:

    int output = auxInsert(&(t->root), newNode); // insere o nó na posição correta
    if(output == Error){ free(newNode); } // Caso a árvore já possua aquele item, desaloca o newNode (evitar memory leak)

    return output;
}

// função interna que vai remover o nó cujo item possui a menor chave
// da subárvore com raiz *current e retornar esse nó
node *popLowest(node **current){
    // caso o nó atual seja o mais à esquerda dessa subárvore (menor chave)
    if((*current)->left == NULL){
        return *current; // retorna o nó de menor chave
    }

    // caso o nó à esquerda do atual seja o mais à esquerda dessa subárvore (menor chave)
    else if((*current)->left->left == NULL){
        node *tmp = (*current)->left; // salva o nó à esquerda do atual (o de menor chave) na variável temporária
        (*current)->left = tmp->right; // reconstrói a ligação para removê-lo (faz a subárvore à esquerda do atual
                                        // apontar para o que estava à direita do de menor chave (que agora é apotado pela tmp)

        return tmp; // retorna o nó de menor chave
    }

    return popLowest(&((*current)->left)); // recursivamente procura pelo nó de menor chave
}

// função interna que procura o nó a ser removido (com chave key)
// na subárvore com raiz *current
int auxRemove(node **current, char *key){
    // caso chegue-se a um nó nulo, significa que o nó a ser removido não está na árvore
    if(*current == NULL){ return Error; } 

    // caso a chave procurada seja menor do que a do nó atual, ela está na subárvore esquerda
    // então recursivamente a procura nessa subárvore
    else if(strcmp((*current)->word.string, key) > 0){ return auxRemove(&((*current)->left), key); }

    // caso seja maior, subárvore direita
    else if(strcmp((*current)->word.string, key) < 0){ return auxRemove(&((*current)->right), key); }

    // caso seja igual, o nó a ser removido foi encontrado
    else{
        // caso o nó seja uma folha, basta removê-lo
        if((*current)->left == NULL && (*current)->right == NULL){  
            free(*current); // desaloca ele
            *current = NULL;
            return 1;
        }
        
        node *left = (*current)->left; // subárvore à esquerda do nó
        node *right = (*current)->right; //  ||    || direita  || ||

        // variável temporária
        node *tmp = (left == NULL) // caso não haja uma subárvore à esquerda
            ? right // salva a raiz da subárvore à direita na variável temporária
            : (right == NULL) // caso haja uma subárvore esquerda e não haja uma direita
                ? left // salva a raiz da subárvore à esquerda na variável temporária
                : popLowest(&((*current)->right)); // e caso subárvores de ambos os lados, dá um pop
                                                   // no nó mais à esquerda da subárvore à direita para a tmp

        free(*current); // desaloca o nó atual (removendo-o)
        *current = tmp; // e coloca o nó salvo na variável temporária em seu lugar

        // refaz as ligações
        if(*current != right){ (*current)->right = right; }
        if(*current != left){ (*current)->left = left; }

        return Success;
    }
}

int bst_remove(bst *t, char *key){
    return (t != NULL) ? auxRemove(&(t->root), key) : Error;
}

// função interna para recursivamente buscar o nó com chave key
// na subárvore com raiz current
item auxSearch(node *current, char *key){
    return (current == NULL) // se chegar num nó nulo, significa que a chave buscada não está na árvore
        ? ErrorItem // nesse caso, retorna um erro
        : (strcmp(current->word.string, key) == 0) // caso contrário, verifica se o nó atual possui a chave buscada
            ? current->word // se sim, retorna o item neste nó
            : (strcmp(current->word.string, key) > 0) // se não, verifica em qual subárvore (esquerda ou direita) a chave deve está
                ? auxSearch(current->left, key) // e recursivamente busca ela
                : auxSearch(current->right, key);
}

item bst_search(bst *t, char *key){
    return (t != NULL) ? auxSearch(t->root, key) : ErrorItem;
}

// função interna para calcular a altura da (sub)árvore de raiz root com bruteforce
int auxHeight(node *root){
    if(root == NULL){ return 0; } // caso a raiz seja nula, a altura é 0

    // recursivamente calcula as alturas das subárvores
    // à esquerda e à direita
    int left = auxHeight(root->left);
    int right = auxHeight(root->right);

    // a altura dessa subárvore vai ser 1 + o máx entre a das subárvores esquerda e direita
    return (left > right ? left : right) + 1;
}

int bst_getHeight(bst *t){
    return (t != NULL) ? auxHeight(t->root) - 1 : Error; // caso a árvore exista, retorna sua altura
}

// recursivamente printa em ordem a subárvore com raiz *current
void auxPrint(node *current){
    if(current != NULL){
        auxPrint(current->left);
        printf("%s %d\n", current->word.string, current->word.occurrences);
        auxPrint(current->right);
    }

    return;
}

void bst_print(bst *t){
    (t != NULL) ? auxPrint(t->root) : printf("%d\n", Error);
    
    return;
}