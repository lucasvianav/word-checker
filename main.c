/*
    Daniel Carvalho Dantas 10685702
    Lucas Viana Vilela 10748409
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ADTs/bst.h"
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
void update_words(bst** dictionary, int id){
    
    char operation_char;
    char* current_word = (char*)malloc(20* sizeof(char));

    while(scanf(" %c",&operation_char)){

        if(operation_char == '#') return; 

        // Remoção
        if(operation_char == '0'){

            scanf("%s",current_word);
            
            int result = bst_remove(dictionary[id],current_word);
            
            if(result == 1) {printf("%s EXCLUIDA DE %d\n",current_word,id + 1);}
            
            else{
                printf("%s INEXISTENTE EM %d\n",current_word,id + 1);
            }
        }

        // Inserção
        else{

            scanf("%s",current_word);

            item search_item = bst_search(dictionary[id],current_word);
            
            // Palavra não existe na árvore
            if(strcmp(search_item.string,ErrorStr) == 0){
                
                bst_insert(dictionary[id],current_word);
                
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
void insert_words(bst** dictionary, int id){
    
    char* current_word = (char*)malloc(20*sizeof(char));

    while(scanf("%s",current_word)){

        if(current_word[0] == '#') return; // Sai da função quando encontra o #

        bst_insert(dictionary[id],current_word);
    }

    free(current_word);

    return ;
}


int get_new_dict_id(bst **dictionaries){
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
    bst** dicts;
    dicts = (bst**)malloc(3 * sizeof(bst*));

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
            dicts[current_dictionary] = bst_new(); 
            
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
                bst_delete(&dicts[current_dictionary - 1]);
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

            //bst* input_tree  = bst_new();
            break;

            default:
            break;

        }
    }

    bst_print(dicts[0]);

    // Desaloca os dicionários
    for(i = 0; i < 3; i++){
        free(dicts[i]);
    }

    free(dicts);

    return 0;
}