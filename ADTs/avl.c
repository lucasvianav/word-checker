/*
    Daniel Carvalho Dantas 10685702
    Lucas Viana Vilela 10748409
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./avl.h"

#define max(x, y) (x > y ? x : y)

struct node_ {
    char *word;
    int height; // altura do nó
    struct node_ *left; // subárvore à esquerda do nó
    struct node_ *right; // subárvore à direita do nó
};
typedef struct node_ node;

struct avl_ {
    node *root;
};


avl *avl_new(){
    avl *tree = (avl *)malloc(sizeof(avl)); // aloca uma nova AVL
    if(tree == NULL){ return NULL; } // verifica se a alocação foi bem-sucedida

    tree->root = NULL; // anula a raiz

    return tree;
}

// essa e todas as outras funções 'aux' (auxiliar) são internas
// desaloca todos os nós da subárvore com *current como raiz
void avl_auxDelete(node **current){
    if(*current != NULL){ // garante que só vai percorrer os nós até encontrar uma folha
        avl_auxDelete(&((*current)->left)); // recursivamente deleta a subárvore à esquerda desse nó
        avl_auxDelete(&((*current)->right)); // ||              ||  ||    ||    ||  direita   ||  ||

        // após desalocar as subárvores esquerda e direita, faz o mesmo pra raiz
        // (percurso pós-ordem)

        free((*current)->word); // desaloca a string do nó raiz
        free(*current); // desaloca o nó-raiz
        *current = NULL;
    }

    return;
}

int avl_delete(avl **t){
    if(*t == NULL){ return Error; } // verifica se a AVL existe

    avl_auxDelete(&((*t)->root)); // desaloca todos os nós da lista

    free(*t); // desaloca a árvore
    *t = NULL;

    return Success;
}

// retorna a altura do nó n
// (função interna)
int getNodeHeight(node *n){
    return (n != NULL) ? n->height : -1;
}

// atualiza a altura do nó n
// (função interna)
void updateNodeHeight(node *n){
    // vai ser o máximo entre as alturas dos filhos + 1
    if(n != NULL){n->height = max(getNodeHeight(n->right), getNodeHeight(n->left)) + 1; }
    return;
}

// rotaciona o nó n no sentido horário (rotação para a direita)
// retorna o nó que vai assumir o lugar de n (o que antes estava à esquerda)
// (função interna)
node *clockwiseRotation(node *n){
    node *aux = n->left;
    n->left = aux->right;
    aux->right = n;

    updateNodeHeight(n);
    updateNodeHeight(aux);

    return aux;
}

// rotaciona o nó n no sentido anti-horário (rotação para a esquerda)
// retorna o nó que vai assumir o lugar de n (o que antes estava à direita)
// (função interna)
node *counterClockwiseRotation(node *n){
    node *aux = n->right;
    n->right = aux->left;
    aux->left = n;

    updateNodeHeight(n);
    updateNodeHeight(aux);

    return aux;
}

// função interna que insere o nó new na posição correta no interior
// da subárvore com raiz *current
// vai incrementar height para cada nível que descer na árvore
// no total, vai somar comprimento do percurso feito + 1 ao valor
// inicial de height
int avl_auxInsert(node **current, node *new){
    if(*current == NULL){ // caso base --> a posição correta para o novo nó foi encontrada
        *current = new; // insere na posição
        return Success;
    }

    // caso contrário:

    // se a palavra do nó atual for igual ao do novo nó
    if(strcmp((*current)->word, new->word) == 0){ return Error; }

    // se a palavra do nó atual alfabeticamente viria depois da do novo nó
    // recursivamente procura a posição para inserir na subárvore esquerda
    // caso contrário, faz o mesmo pra subárvore direita
    int output = avl_auxInsert( (strcmp((*current)->word, new->word) > 0) ? &((*current)->left) : &((*current)->right), new );

    // se a inserção tiver sido bem-sucedida
    if(output == Success){
        // caso o fator de balanceamento do nó atual seja maior que 1, faz as rotações necessárias
        if(getNodeHeight((*current)->left) - getNodeHeight((*current)->right) >= 2){
            // se o fator de balanceamento do nó à esquerda for negativo, rotaciona ele no sentido anti-horário
            if((*current)->left != NULL && getNodeHeight((*current)->left->left) - getNodeHeight((*current)->left->right) < 0){
                (*current)->left = counterClockwiseRotation((*current)->left);
            }

            // rotaciona o nó atual no sentido horário
            *current = clockwiseRotation(*current);
        }

        // caso o fator de balanceamento do nó atual seja menor que -1, faz as rotações necessárias
        else if(getNodeHeight((*current)->left) - getNodeHeight((*current)->right) <= -2){
            // se o fator de balanceamento do nó à direita for positivo, rotaciona ele no sentido horário
            if((*current)->right != NULL && getNodeHeight((*current)->right->left) - getNodeHeight((*current)->right->right) > 0){
                (*current)->right = clockwiseRotation((*current)->right); 
            }

            // rotaciona o nó atual no sentido anti-horário
            *current = counterClockwiseRotation(*current);
        }

        // caso nenhuma rotação seja necessária, apenas atualiza a altura do nó atual
        else{ updateNodeHeight(*current); }
    }

    return output;
}

int avl_insert(avl *t, char *word){
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
    newNode->word = newWord;
    newNode->height = 0;
    newNode->left = NULL;
    newNode->right = NULL;

    // caso a árvore esteja vazia
    if(t->root == NULL){
        t->root = newNode; // insere o nó na raiz
        return Success;
    }

    // caso não esteja vazia:

    // tenta inserir o nó na posição correta
    int output = avl_auxInsert(&(t->root), newNode); 

    // Caso a árvore já possua aquele item libera 
    // a memória alocada (evitar memory leak)
    if(output == Error){  
        free(newNode->word);
        free(newNode); 
    }

    return output;
}

// função interna que vai remover o nó cujo char *possui a menor chave
// da subárvore com raiz *current e retornar esse nó
node *avl_pullLowest(node **current){
    node *tmp;  // variável temporária

    // caso o nó atual seja o mais à esquerda dessa subárvore (menor chave)
    if((*current)->left == NULL){
        tmp = *current; // salva ele na variável temporária

        // reconstrói a ligação para removê-lo da árvore, 
        // substituindo-o pelo que está à sua direita
        *current = tmp->right;

        tmp->right = NULL;

        return tmp; // retorna o nó de menor chave
    } 

    // caso o nó à esquerda do atual seja o mais à esquerda dessa subárvore (menor chave)
    else if(((*current)->left)->left == NULL){
        tmp = (*current)->left; // salva o nó à esquerda do atual (o de menor chave) na variável temporária

        // reconstrói a ligação para removê-lo (faz a subárvore à esquerda do atual
        // apontar para o que estava à direita do de menor chave (que agora é apotado pela tmp)
        (*current)->left = tmp->right; 

        return tmp; // retorna o nó de menor chave
    }

    // recursivamente procura pelo nó de menor chave, caso ele ainda não tenha sido encontrado
    return avl_pullLowest(&((*current)->left));
}

// função interna que procura o nó a ser removido (com palavra key)
// na subárvore com raiz *current
int avl_auxRemove(node **current, char *key){
    // caso chegue-se a um nó nulo, significa que o nó a ser removido não está na árvore
    if(*current == NULL){ return Error; } 

    // caso a palavra procurada seja igual à do nó atual, o nó a ser removido foi encontrado
    else if(strcmp((*current)->word, key) == 0){
        // caso o nó seja uma folha, basta removê-lo
        if((*current)->left == NULL && (*current)->right == NULL){  
            free((*current)->word); // desaloca a string dele
            free(*current); // desaloca ele
            *current = NULL;
            return Success;
        }
        
        node *left = (*current)->left; // subárvore à esquerda do nó
        node *right = (*current)->right; //  ||    || direita  || ||

        // variável temporária
        node *tmp;

        // caso não haja uma subárvore à esquerda, salva 
        // a raiz da subárvore à direita na variável temporária
        if(left == NULL){ 
            tmp = right; 
        }

        // caso haja uma subárvore esquerda e não haja uma direita
        // salva a raiz da subárvore à esquerda na variável temporária
        else if(right == NULL){ 
            tmp = left; 
        }

        // e caso subárvores de ambos os lados, dá um pop
        // no nó mais à esquerda da subárvore à direita para a tmp
        else{ 
            tmp = avl_pullLowest(&((*current)->right));

            // e refaz as ligações
            if(tmp != right){ tmp->right = right; }
            if(tmp != left){ tmp->left = left; }
        }

        free((*current)->word); // desaloca a string do nó atual
        free(*current); // desaloca o nó atual (removendo-o)
        *current = tmp; // e coloca o nó salvo na variável temporária em seu lugar

        updateNodeHeight(*current); // atualiza a altura do nó atual

        return Success;
    }

    // caso a chave procurada seja menor do que a do nó atual, ela está na subárvore esquerda
    // caso seja maior, subárvore direita. recursivamente procura na subárvore adequada
    int output = avl_auxRemove((strcmp((*current)->word, key) > 0) ? &((*current)->left) : &((*current)->right), key);

    // se a remoção tiver sido bem-sucedida
    if(output == Success){
        // caso o fator de balanceamento do nó atual seja maior que 1, faz as rotações necessárias
        if(getNodeHeight((*current)->left) - getNodeHeight((*current)->right) >= 2){
            // se o fator de balanceamento do nó à esquerda for negativo, rotaciona ele no sentido anti-horário
            if((*current)->left != NULL && getNodeHeight((*current)->left->left) - getNodeHeight((*current)->left->right) < 0){
                (*current)->left = counterClockwiseRotation((*current)->left);
            }

            // rotaciona o nó atual no sentido horário
            *current = clockwiseRotation(*current);
        }

        // caso o fator de balanceamento do nó atual seja menor que -1, faz as rotações necessárias
        else if(getNodeHeight((*current)->left) - getNodeHeight((*current)->right) <= -2){
            // se o fator de balanceamento do nó à direita for positivo, rotaciona ele no sentido horário
            if((*current)->right != NULL && getNodeHeight((*current)->right->left) - getNodeHeight((*current)->right->right) > 0){
                (*current)->right = clockwiseRotation((*current)->right); 
            }

            // rotaciona o nó atual no sentido anti-horário
            *current = counterClockwiseRotation(*current);
        }

        // caso nenhuma rotação seja necessária, apenas atualiza a altura do nó atual
        else{ updateNodeHeight(*current); }
    }

    return output;
}

int avl_remove(avl *t, char *key){
    return (t != NULL) ? avl_auxRemove(&(t->root), key) : Error;
}

// função interna para recursivamente buscar o nó com chave key
// na subárvore com raiz current
int avl_auxSearch(node *current, char *key){
    return (current == NULL) // se chegar num nó nulo, significa que a chave buscada não está na árvore
        ? Error // nesse caso, retorna um erro
        : (strcmp(current->word, key) == 0) // caso contrário, verifica se o nó atual possui a chave buscada
            ? current->height // se sim, retorna a altura deste nó
            : (strcmp(current->word, key) > 0) // se não, verifica em qual subárvore (esquerda ou direita) a chave deve está
                ? avl_auxSearch(current->left, key) // e recursivamente busca ela
                : avl_auxSearch(current->right, key);
}

int avl_search(avl *t, char *key){
    return (t != NULL) ? avl_auxSearch(t->root, key) : Error;
}

int avl_getHeight(avl *t){
    return getNodeHeight(t->root); // a altura da raiz é a altura da árvore
}

// recursivamente printa em ordem a subárvore com raiz *current
void avl_auxPrint(node *current){
    if(current != NULL){
        avl_auxPrint(current->left);
        printf("%s\n", current->word);
        avl_auxPrint(current->right);
    }

    return;
}

void avl_print(avl *t){
    (t != NULL) ? avl_auxPrint(t->root) : printf("%d\n", Error);
    
    return;
}