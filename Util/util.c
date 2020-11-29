/*
    Daniel Carvalho Dantas 10685702
    Lucas Viana Vilela 10748409
*/

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "util.h"

void removeHashtag(char *string){
    int i = 0;
    while(string[i] != '#'){ i++; }
    string[i] = '\0';

    return;
}