#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "entradas.h"
#include "arvores.h"
#include "colisoes.h"

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

    //printarDados(&lista);

    raizes = inicializaArvores(TIME);

    if(!raizes){
        printf("Erro na inicialização da árvore.");
        exit(1);
    }

    entrada = (lista)->first;

    while(entrada){

        Node* raiz = construirArvores(&entrada,&raizes);

        if(!raiz){
            printf("Erro na construção das árvores.");
            exit(1);    
        }

        checarColisoesParciais(&entrada,&raizes,&lista);
        checarColisoesTotais(&entrada,&raizes,&lista);

        entrada = entrada->prox;
    }

    Node* r = raizes;

    FILE* arquivoSaida = fopen("saida.txt", "w");  // Abre o arquivo "saida.txt" no modo de escrita
    exibirArvore(&r,0, arquivoSaida);
    fclose(arquivoSaida);  // Fecha o arquivo de saída quando terminar

    getchar();

    return 0;
}