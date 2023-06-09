#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "entradas.h"
#include "arvores.h"

Node* raizes;
noDescritor* entrada;
Dado* atual;
DadosEntrada insercao;

int main() {

    int aux;

    entrada = NULL;

    aux = lerDados(&entrada);

    if(!aux){
        printf("Erro na leitura dos dados");
        exit(1);
    }

    printarDados(&entrada);

    raizes = inicializaArvores(TIME);

    if(!raizes){
        printf("Erro na inicialização da arvore.");
        exit(1);
    }


    atual = (entrada)->first;

    while(atual){
        printf("%s ", atual->solution.teacherName);
        atual = atual->prox;
    }

    


    getchar();

    return 0;
}