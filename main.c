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

// Atualiza as palavras do dicionário
void update_words(bst** dictionary, int id){
    
    char current_word[20];
    int operation = 0;

    while(scanf("%d %s",&operation,current_word)){

        if(current_word[0] == '#') return; // FALTA CORRIGIR

        // Remoção
        if(operation == 0){
            
            int result = bst_remove(dictionary[id],current_word);
            
            if(result == 1) {printf("%s EXCLUIDA DE %d\n",current_word,id);}
            
            else{
                printf("%s INEXISTENTE EM %d\n",current_word,id);
            }
        }

        // Inserção
        else{

            item search_item = bst_search(dictionary[id],current_word);
            
            // Palavra não existe na árvore
            if(strcmp(search_item.string,ErrorStr) == 0){
                item new_item = {current_word,1};
                bst_insert(dictionary[id],new_item);
                
                printf("%s INSERIDA EM %d\n",current_word,id);
            }
            else{ // Palavra já existe na árvore
                printf("%s JA EXISTE EM %d\n",current_word,id);
            }
        } 
    }
    return ;
}

// Insere novas palavras no dicionário recém-criado
void insert_words(bst** dictionary, int id){
    
    char current_word[20];

    while(scanf("%s",current_word)){

        if(current_word[0] == '#') return; // Sai da função quando encontra o #

        item current_item = {current_word,1};

        bst_insert(dictionary[id],current_item);
    }

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

            printf("DICIONARIO %d CRIADO\n",current_dictionary);
            num_dictionaries++;

            break;

            // Atualizar
            case 2:

            scanf("%d",&current_dictionary);

            // Inexistente
            if(dicts[current_dictionary] == NULL){
                printf("DICIONARIO %d INEXISTENTE\n",current_dictionary);
                break;
            }

            update_words(dicts,current_dictionary);

            break;

            // Excluir
            case 3:
            scanf("%d",&current_dictionary);

            // Inexistente
            if(dicts[current_dictionary] == NULL){
                printf("DICIONARIO %d INEXISTENTE\n",current_dictionary);
                break;
            }

            // Quando diferente de NULL
            else{
                bst_delete(&dicts[current_dictionary]);
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

    // Desaloca os dicionários
    for(i = 0; i < 3; i++){
        free(dicts[i]);
    }

    free(dicts);

    return 0;
}