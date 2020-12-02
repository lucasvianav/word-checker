/*
    ARQUIVO PARA TESTES GENÉRICOS
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){

    int n;
    float f;
    printf("Please enter an integer: ");
    while(scanf("%f",&f)!=1 || (int)f != f){
        printf("oi\n");
    }


    return 0;
}