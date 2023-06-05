#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "entradas.h"

int main() {

    noDescritor* entrada = NULL;

    int aux = lerDados(&entrada);

    if(!aux){
        printf("Erro na leitura dos dados");
        exit(1);
    }

    printarDados(&entrada);

    getchar();

    return 0;
}