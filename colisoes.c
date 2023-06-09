#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "entradas.h"
#include "arvores.h"

Node* raizes;
noDescritor* lista;
Dado* entrada;

int main() {

    int aux;

    entrada = NULL;

    aux = lerDados(&lista);

    if(!aux){
        printf("Erro na leitura dos dados");
        exit(1);
    }

    printarDados(&lista);

    raizes = inicializaArvores(TIME);

    if(!raizes){
        printf("Erro na inicialização da árvore.");
        exit(1);
    }

    entrada = (lista)->first;

    while(entrada){

        aux = construirArvores(&entrada,&raizes);

        if(!aux){
            printf("Erro na construção das árvores.");
            exit(1);    
        }

        entrada = entrada->prox;
    }

    exibirArvore(&raizes);

    getchar();

    return 0;
}