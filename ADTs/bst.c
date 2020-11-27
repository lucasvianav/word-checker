#include <stdio.h>
#include <stdlib.h>
#include "./abb.h"

struct node_ {
    item movie;
    struct node_ *left; // subárvore à esquerda do nó
    struct node_ *right; // subárvore à direita do nó
};
typedef struct node_ node;

struct bst_ {
    node *root;
    int height; // altura da árvore
};


bst *bst_new(){
    bst *tree = (bst *)malloc(sizeof(bst)); // aloca uma nova BST

    if(tree == NULL){ return NULL; } // verifica se a alocação foi bem-sucedida

    tree->root = NULL; // anula a raiz
    tree->height = 0; // inicia a altura da árvore como 0

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

    return 1;
}

// função interna que insere o nó new na posição correta no interior
// da subárvore com raiz *current
// vai incrementar height para cada nível que descer na árvore
// no total, vai somar comprimento do percurso feito + 1 ao valor
// inicial de height
int auxInsert(node **current, node *new, int *height){
    (*height)++;

    if(*current == NULL){ // caso base --> a posição correta para o novo nó foi encontrada
        *current = new; // insere na posição
        return 1;
    }

    // caso contrário:

    return ((*current)->movie.key > new->movie.key) // se a chave do nó atual for maior do que a do novo nó
        ? auxInsert(&((*current)->left), new, height) // recursivamente procura a posição para inserir na subárvore esquerda
        : ((*current)->movie.key < new->movie.key) // se for menor
            ? auxInsert(&((*current)->right), new, height) // faz o mesmo na subárvore direita
            : Error; // se for igual, retorna erro (o item do novo nó já está contido na árvore)
}

int bst_insert(bst *t, item movie){
    node *newNode = (node *)malloc(sizeof(node)); // aloca um novo nó

    // checa se a árvore existe e se a alocação
    // do novo nó foi bem-sucedida
    if(t == NULL || newNode == NULL){ 
        if(newNode != NULL){ free(newNode); }
        return Error; 
    }

    // ajusta as informações do novo nó
    newNode->movie = movie;
    newNode->left = NULL;
    newNode->right = NULL;

    // caso a árvore esteja vazia
    if(t->root == NULL){
        t->root = newNode; // insere o nó na raiz
        // e a altura permanece em 0
        return 1;
    }

    // caso não esteja vazia:

    int height = -1; // variável que será usada para calcular a altura na auxInsert
    int output = auxInsert(&(t->root), newNode, &height); // insere o nó na posição correta e calcula a altura

    if(output == Error){ free(newNode); } // Caso a árvore já possua aquele item, desaloca o newNode (evitar memory leak)

    t->height += (t->height < height) ? 1 : 0; // ajusta a altura da árvore com base no valor calculado

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
int auxRemove(node **current, int key){
    // caso chegue-se a um nó nulo, significa que o nó a ser removido não está na árvore
    if(*current == NULL){ return Error; } 

    // caso a chave procurada seja menor do que a do nó atual, ela está na subárvore esquerda
    // então recursivamente a procura nessa subárvore
    else if(key < (*current)->movie.key){ return auxRemove(&((*current)->left), key); }

    // caso seja maior, subárvore direita
    else if(key > (*current)->movie.key){ return auxRemove(&((*current)->right), key); }

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

        return 1;
    }
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

int bst_remove(bst *t, int key){
    if(t == NULL || t->height == 0){ return Error; } // verifica se a árvore existe e não está vazia

    int output = auxRemove(&(t->root), key); // remove o nó desejado
    t->height = (output != Error) ? (auxHeight(t->root) - 1) : t->height; // ajusta a altura da árvore caso necessário

    return output;
}

// função interna para recursivamente buscar o nó com chave key
// na subárvore com raiz current
char *auxSearch(node *current, int key){
    return (current == NULL) // se chegar num nó nulo, significa que a chave buscada não está na árvore
        ? ErrorStr // nesse caso, retorna um erro
        : (key == current->movie.key) // caso contrário, verifica se o nó atual possui a chave buscada
            ? current->movie.title // se sim, retorna o título do item neste nó
            : (key < current->movie.key) // se não, verifica em qual subárvore (esquerda ou direita) a chave deve está
                ? auxSearch(current->left, key) // e recursivamente busca ela
                : auxSearch(current->right, key);
}

char *bst_search(bst *t, int key){
    return (t != NULL) ? auxSearch(t->root, key) : ErrorStr;
}

int bst_getHeight(bst *t){
    return (t != NULL) ? t->height : Error; // caso a árvore exista, retorna sua altura
}

// recursivamente printa em ordem a subárvore com raiz *current
void auxPrint(node *current){
    if(current != NULL){
        auxPrint(current->left);
        printf("%d %s\n", current->movie.key, current->movie.title);
        auxPrint(current->right);
    }

    return;
}

void bst_print(bst *t){
    if (t == NULL){ printf("%d\n", Error); }
    else if(t->height > 0){ auxPrint(t->root); } // printa a árvore toda em ordem, caso ela não esteja vazia
    return;
}