#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "entradas.h"
#include "arvores.h"
#include "colisoes.h"

//variáveis globais para utilização do programa
Node* raizes;
noDescritor* lista;
Dado* entrada;

int main() {

    int aux;

    entrada = NULL;

    //Leitura dos dados do arquivo csv sendo guardados em uma lista linear
    aux = lerDados(&lista);

    if(!aux){
        printf("Erro na leitura dos dados");
        exit(1);
    }

    //Aloca espaço na memória para uma raiz com id = 0 (indica que não há informações inseridas)
    raizes = inicializaArvores(TIME);

    if(!raizes){
        printf("Erro na inicialização da árvore.");
        exit(1);
    }

    entrada = (lista)->first;

    //iteração por cada nó da lista para inserção nas árvores
    while(entrada){

        //insere as informações na árvore e retorna o endereço da raiz escolhida
        Node* raiz = construirArvores(&entrada,&raizes);

        if(!raiz){
            printf("Erro na construção das árvores.");
            exit(1);    
        }

        //checa e grava as colisões
        checarColisoesParciais(&entrada,&raizes);
        checarColisoesTotais(&entrada,&raiz);

        entrada = entrada->prox;
    }

    Node* r = raizes;

    FILE* arquivoSaida = fopen("saida.txt", "w");  // Abre o arquivo "saida.txt" no modo de escrita

    //grava a saída com as colisões no arquivo saida.csv
    printarDados(&lista,arquivoSaida);

    fclose(arquivoSaida);  // Fecha o arquivo de saída quando terminar

    printf("\nARQUIVO saida.txt GERADO COM AS INFORMACOES DAS COLISOES!\n");
    printf("Pressione Enter para sair.");

    getchar();

    return 0;
}