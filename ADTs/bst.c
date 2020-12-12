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
void bst_auxDelete(node **current){
    if(*current != NULL){ // garante que só vai percorrer os nós até encontrar uma folha
        bst_auxDelete(&((*current)->left)); // recursivamente deleta a subárvore à esquerda desse nó
        bst_auxDelete(&((*current)->right)); // ||              ||  ||    ||    ||  direita   ||  ||

        // após desalocar as subárvores esquerda e direita, faz o mesmo pra raiz
        // (percurso pós-ordem)

        free((*current)->word.string); // desaloca a string do nó raiz
        free(*current); // desaloca o nó-raiz
        *current = NULL;
    }

    return;
}

int bst_delete(bst **t){
    if(*t == NULL){ return Error; } // verifica se a BST existe

    bst_auxDelete(&((*t)->root)); // desaloca todos os nós da lista

    free(*t); // desaloca a árvore
    *t = NULL;

    return Success;
}

// função interna que insere o nó new na posição correta no interior
// da subárvore com raiz *current
// vai incrementar height para cada nível que descer na árvore
// no total, vai somar comprimento do percurso feito + 1 ao valor
// inicial de height
int bst_auxInsert(node **current, node *new){
    if(*current == NULL){ // caso base --> a posição correta para o novo nó foi encontrada
        *current = new; // insere na posição
        return Success;
    }

    // caso contrário:

    // se a palavra do nó atual for igual ao do novo nó
    if(strcmp((*current)->word.string, new->word.string) == 0){ 
        (*current)->word.occurrences += 1; // incrementa o número de ocorrências dela
        return Error;
    }

    // se a palavra do nó atual alfabeticamente viria depois da do novo nó
    else if(strcmp((*current)->word.string, new->word.string) > 0){
        return bst_auxInsert(&((*current)->left), new); // recursivamente procura a posição para inserir na subárvore esquerda
    }

    // caso contrário, faz o mesmo pra subárvore direita
    else{ return bst_auxInsert(&((*current)->right), new); }
}

int bst_insert(bst *t, char *word){
    node *newNode = (node *)malloc(sizeof(node)); // aloca um novo nó
    char *newWord = (char *)malloc((strlen(word) + 1) * sizeof(char)); // aloca uma sting para aquele nó

    // checa se a árvore existe e se a alocação do novo nó foi bem-sucedida
    // caso contrário, libera a memória alocada (se alocada)
    if(t == NULL || newNode == NULL || newWord == NULL){ 
        if(newNode != NULL){ free(newNode); }
        if(newWord != NULL){ free(newWord); }
        return Error; 
    }

    // copia a palavra recebida para a string alocada
    strcpy(newWord, word);

    // ajusta as informações do novo nó
    newNode->word = (item) {newWord, 1};
    newNode->left = NULL;
    newNode->right = NULL;

    // caso a árvore esteja vazia
    if(t->root == NULL){
        t->root = newNode; // insere o nó na raiz
        return Success;
    }

    // caso não esteja vazia:

    // tenta inserir o nó na posição correta e caso a árvore já possua
    // aquele item, libera a memória alocada (evitar memory leak)
    if(bst_auxInsert(&(t->root), newNode) == Error){
        free(newWord);
        free(newNode); 
        newWord = NULL;
        newNode = NULL;
    }

    return Success;
}

// função interna que vai remover o nó cujo item possui a menor chave
// da subárvore com raiz *current e retornar esse nó
node *bst_pullLowest(node **current){
    node *tmp; // variável temporária

    // caso o nó atual seja o mais à esquerda dessa subárvore (menor chave)
    if((*current)->left == NULL){
        tmp = *current; // salva ele na variável temporária

        // reconstrói a ligação para removê-lo da árvore, 
        // substituindo-o pelo que está à sua direita
        *current = tmp->right; 

        return tmp; // retorna o nó de menor chave
    }

    // caso o nó à esquerda do atual seja o mais à esquerda dessa subárvore (menor chave)
    else if(((*current)->left)->left == NULL){
        tmp = (*current)->left; // salva o nó à esquerda do atual (o de menor chave) na variável temporária

        // reconstrói a ligação para removê-lo (faz a subárvore à esquerda do atual
        // apontar para o que estava à direita do de menor chave, que agora é apotado pela tmp)
        (*current)->left = tmp->right; 
                                        

        return tmp; // retorna o nó de menor chave
    }

    // recursivamente procura pelo nó de menor chave, caso ele ainda não tenha sido encontrado
    return bst_pullLowest(&((*current)->left)); 
}

// função interna que procura o nó a ser removido (com palavra key)
// na subárvore com raiz *current
int bst_auxRemove(node **current, char *key){
    // caso chegue-se a um nó nulo, significa que o nó a ser removido não está na árvore
    if(*current == NULL){ return Error; } 

    // caso a chave procurada seja menor do que a do nó atual, ela está na subárvore esquerda
    // então recursivamente a procura nessa subárvore
    else if(strcmp((*current)->word.string, key) > 0){ return bst_auxRemove(&((*current)->left), key); }

    // caso seja maior, subárvore direita
    else if(strcmp((*current)->word.string, key) < 0){ return bst_auxRemove(&((*current)->right), key); }

    // caso seja igual, o nó a ser removido foi encontrado
    else{
        // caso o nó seja uma folha, basta removê-lo
        if((*current)->left == NULL && (*current)->right == NULL){  
            free((*current)->word.string); // desaloca a string dele
            free(*current); // desaloca ele
            *current = NULL;

            return Success;
        }

        // variável temporária
        node *tmp;

        // caso não haja uma subárvore à esquerda, salva 
        // a raiz da subárvore à direita na variável temporária
        if((*current)->left == NULL){ 
            tmp = (*current)->right; 
        }

        // caso haja uma subárvore esquerda e não haja uma direita
        // salva a raiz da subárvore à esquerda na variável temporária
        else if((*current)->right == NULL){ 
            tmp = (*current)->left; 
        }

        // e caso subárvores de ambos os lados, dá um pull no
        // nó mais à esquerda da subárvore à direita para a tmp
        else{ 
            tmp = bst_pullLowest(&((*current)->right));

            // e refaz as ligações
            if(tmp != (*current)->right){ tmp->right = (*current)->right; }
            if(tmp != (*current)->left){ tmp->left = (*current)->left; }
        }

        free((*current)->word.string); // desaloca a string do nó atual
        free(*current); // desaloca o nó atual (removendo-o)
        *current = tmp; // e coloca o nó salvo na variável temporária em seu lugar
        tmp = NULL;

        return Success;
    }
}

int bst_remove(bst *t, char *key){
    return (t != NULL) ? bst_auxRemove(&(t->root), key) : Error;
}

// função interna para recursivamente buscar o nó com chave key
// na subárvore com raiz current
item bst_auxSearch(node *current, char *key){
    return (current == NULL) // se chegar num nó nulo, significa que a chave buscada não está na árvore
        ? ErrorItem // nesse caso, retorna um erro
        : (strcmp(current->word.string, key) == 0) // caso contrário, verifica se o nó atual possui a chave buscada
            ? current->word // se sim, retorna o item neste nó
            : (strcmp(current->word.string, key) > 0) // se não, verifica em qual subárvore (esquerda ou direita) a chave deve está
                ? bst_auxSearch(current->left, key) // e recursivamente busca ela
                : bst_auxSearch(current->right, key);
}

item bst_search(bst *t, char *key){
    return (t != NULL) ? bst_auxSearch(t->root, key) : ErrorItem;
}

// função interna para calcular a altura da (sub)árvore de raiz root com bruteforce
int bst_auxHeight(node *root){
    if(root == NULL){ return 0; } // caso a raiz seja nula, a altura é 0

    // recursivamente calcula as alturas das subárvores
    // à esquerda e à direita
    int left = bst_auxHeight(root->left);
    int right = bst_auxHeight(root->right);

    // a altura dessa subárvore vai ser 1 + o máx entre a das subárvores esquerda e direita
    return (left > right ? left : right) + 1;
}

int bst_getHeight(bst *t){
    return (t != NULL) ? bst_auxHeight(t->root) - 1 : Error; // caso a árvore exista, retorna sua altura
}

// recursivamente printa em ordem a subárvore com raiz *current
// (não printa o número de ocorrências da palavras)
void bst_auxPrint(node *current){
    if(current != NULL){
        bst_auxPrint(current->left);
        printf("%s\n", current->word.string);
        bst_auxPrint(current->right);
    }

    return;
}

void bst_print(bst *t){
    (t != NULL) ? bst_auxPrint(t->root) : printf("%d\n", Error);
    
    return;
}

// recursivamente busca elementos da BST de raiz *current que também
// façam aprte da AVL e faz as operações necessárias com eles
// (percurso em ordem)
void bst_auxIntersection(node **current, avl *AVL, item **array, int *arraySize){
    if(*current != NULL){ // caso base é *current == NULL
        // faz a busca na subárvore à esquerda
        bst_auxIntersection(&((*current)->left), AVL, array, arraySize);

        // verifica se a palavra do nó atual (*current) está na AVL. se estiver:
        if(avl_search(AVL, (*current)->word.string) != Error){
            // aloca uma string com mesmo tamanho da do nó atual
            char *word = (char *)malloc((strlen((*current)->word.string) + 1) * sizeof(char));
            if(word == NULL){ return; } // se a alocação falhar, ocorreu um erro

            // copia a palavra da string do nó atual para a recém-alocada
            strcpy(word, (*current)->word.string);

            // realoca o array de itens para poder incluir o novo (do nó atual)
            *array = (item *)realloc(*array, ++(*arraySize) * sizeof(item));

            // coloca o item do nó atual na última posição do array de itens
            (*array)[*arraySize - 1] = (item) {word, (*current)->word.occurrences};

            // remove o nó atual da BST
            bst_auxRemove(current, (*current)->word.string);

            // faz a busca novamente a partir do novo "nó atual"
            bst_auxIntersection(current, AVL, array, arraySize);
        }

        // caso a palavra do nó atual não esteja na AVL, faz a busca na subárvore à direita
        else{ bst_auxIntersection(&((*current)->right), AVL, array, arraySize); }
    }

    return;
}

item *bst_pullAvlIntersection(bst *BST, avl *AVL, int *arraySize){
    *arraySize = 0; // o array começa com 0 elementos
    item *array = NULL;

    // caso as árvores existam
    if(BST != NULL && AVL != NULL){
        array = (item *)malloc(sizeof(item)); // aloca um elemento pro array

        // e começa a buscar os elementos da intersecção
        if(array != NULL){ bst_auxIntersection(&(BST->root), AVL, &array, arraySize); }
    }

    return array;
}