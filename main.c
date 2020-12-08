/*
    Daniel Carvalho Dantas 10685702
    Lucas Viana Vilela 10748409
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ADTs/bst.h"
#include "ADTs/avl.h"
#include "Util/util.h"

#define MAX_INPUT_SIZE 800

//  Criação da árvore de input

void create_input_tree(bst* input_tree,char* input){

    char* token = strtok(input," ");

    while(token != NULL){

        bst_insert(input_tree,token);   
        token = strtok(NULL," ");               
        }
}


// Atualiza as palavras do dicionário
void update_words(avl** dictionary, int id){
    
    char operation_char;
    char* current_word = (char*)malloc(20* sizeof(char));

    while(scanf(" %c",&operation_char)){

        if(operation_char == '#') return; 

        // Remoção
        if(operation_char == '0'){

            scanf("%s",current_word);
            
            int result = avl_remove(dictionary[id],current_word);
            
            if(result == 1) {printf("%s EXCLUIDA DE %d\n",current_word,id + 1);}
            
            else{
                printf("%s INEXISTENTE EM %d\n",current_word,id + 1);
            }
        }

        // Inserção
        else{

            scanf("%s",current_word);

            int search_result = avl_search(dictionary[id],current_word);
            
            // Palavra não existe na árvore
            if(search_result == Error){
                
                avl_insert(dictionary[id],current_word);
                
                printf("%s INSERIDA EM %d\n",current_word,id + 1);
            }
            else{ // Palavra já existe na árvore
                printf("%s JA EXISTE EM %d\n",current_word,id + 1);
            }
        }
    }
    free(current_word); 
    return ;
}

// Insere novas palavras no dicionário recém-criado
void insert_words(avl** dictionary, int id){
    
    int wordLength;
    char *word;
    char aux;
    
    while(1){
        wordLength = 0;
        word = (char *)malloc(sizeof(char));

        while(1){
            scanf("%c", &aux);

            word = (char *)realloc(word, ++wordLength * sizeof(char));
            word[wordLength-1] = (aux != '\n' && aux != '#' && aux != ' ') ? aux : '\0';

            if(aux == '\n' || aux == '#' || aux == ' '){ break; }
        }

        if(wordLength > 1){ 
            avl_insert(dictionary[id], word); 
        }

        free(word);
        
        if(aux == '#'){ break; }
    }
}

int get_new_dict_id(avl **dictionaries){
    if(dictionaries != NULL){ for(int i = 0; i < MAX_DICTIONARIES; i++){ if(dictionaries[i] == NULL){ return i; } } }
    return Error;
}

int main(){

    // Declaração das variáveis
    int i;
    int n_frequent_words,current_dictionary;
    int operation = 1;
    int num_dictionaries = 0;

    // Aloca espaço para 3 dicionários
    avl** dicts;
    dicts = (avl**)malloc(3 * sizeof(avl*));

    while(operation != 0){

        scanf("%d",&operation);

        switch(operation){

            // Sair
            case 0:
            break;

            // Criar novo dicionário
            case 1:
            
            // Checa o número atual de dicionários
            if(num_dictionaries == 3){
                printf("IMPOSSIVEL CRIAR\n");
                break;
            }

            // Aloca na memória um novo e encontra seu id caso seja possível um novo dicionário
            current_dictionary =  get_new_dict_id(dicts);
            dicts[current_dictionary] = avl_new(); 
            
            insert_words(dicts,current_dictionary);

            // Exibe na tela o número corrigido do dicionário (vetor começa em 0)
            printf("DICIONARIO %d CRIADO\n",current_dictionary + 1);
            num_dictionaries++;

            break;

            // Atualizar
            case 2:

            scanf("%d",&current_dictionary);

            // Inexistente
            if(dicts[current_dictionary - 1] == NULL){
                printf("DICIONARIO %d INEXISTENTE\n",current_dictionary);
                break;
            }

            update_words(dicts,current_dictionary - 1);

            break;

            // Excluir
            case 3:
            scanf("%d",&current_dictionary);

            // Inexistente
            if(dicts[current_dictionary - 1] == NULL){
                printf("DICIONARIO %d INEXISTENTE\n",current_dictionary);
                break;
            }

            // Quando diferente de NULL
            else{
                avl_delete(&dicts[current_dictionary - 1]);
                printf("DICIONARIO %d APAGADO\n",current_dictionary);
                num_dictionaries--;
            }

            break;

            // Verificar
            case 4:

            scanf("%d %d",&current_dictionary,&n_frequent_words);
            
            char* input = NULL;
            fgets(input,MAX_INPUT_SIZE,stdin);
            remove_hashtag(input);

            bst* input_tree  = bst_new();
            create_input_tree(input_tree,input);
            break;

            default:
            break;

        }
    }

    //avl_print(dicts[0]);

    // Desaloca os dicionários
    for(i = 0; i < 3; i++){
        free(dicts[i]);
    }

    free(dicts);

    return 0;
}