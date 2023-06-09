#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvores.h"
#include "entradas.h"

int numRaizes = 0;

Node* criaNovoNo(int TIPOCHAVE){

	Node* novo = (Node*)malloc(sizeof(Node));
	novo->id = 0;
	novo->type = TIPOCHAVE;
	novo->timeSet = NULL;
	novo->child = NULL;
	novo->brother = NULL;
	novo->numChildren = 0;

	return(novo);
}

Node* inicializaArvores(int TIPOCHAVE){
	return(criaNovoNo(TIPOCHAVE));
}

Node* escolheRaiz(Dado** entrada, Node** raizes){

	Node* rootAnterior;
	Node* novaRoot;
	Node* root = (*raizes);

	while(root){
		if(root->id == 0){
			root->id = ++numRaizes;

			Time* time = (Time*)malloc(sizeof(TIME));
			time->idYear = (*entrada)->solution.idYear;
			time->idTerm = (*entrada)->solution.idTerm;
			time->idDay = (*entrada)->solution.idDay;
			time->idBeginSlot = (*entrada)->solution.idBeginSlot;
			time->idEndSlot = (*entrada)->solution.idEndSlot;

			root->timeSet = time;

			return root;

		}

		if(root->timeSet->idYear == (*entrada)->solution.idYear && root->timeSet->idTerm == (*entrada)->solution.idTerm && root->timeSet->idDay == (*entrada)->solution.idDay && root->timeSet->idBeginSlot == (*entrada)->solution.idBeginSlot && root->timeSet->idEndSlot == (*entrada)->solution.idEndSlot){
			return root;
		}

		rootAnterior = root;
		root = root->brother;
	}

	novaRoot = criaNovoNo(TIME);

	novaRoot->id = ++numRaizes;

	Time* time = (Time*)malloc(sizeof(TIME));
	time->idYear = (*entrada)->solution.idYear;
	time->idTerm = (*entrada)->solution.idTerm;
	time->idDay = (*entrada)->solution.idDay;
	time->idBeginSlot = (*entrada)->solution.idBeginSlot;
	time->idEndSlot = (*entrada)->solution.idEndSlot;

	novaRoot->timeSet = time;

	rootAnterior->brother = novaRoot;

	return novaRoot;

}


int construirArvores(Dado** entrada, Node** raizes) {

	Node* raizDeInsercao;

	raizDeInsercao = escolheRaiz(entrada,raizes);

	if(!raizDeInsercao){
		printf("Erro na escolha da raiz.");
        exit(1); 
	}

	printf("%d ", raizDeInsercao->type);

    return SUCESSO;

}

/*

	struct dado* node;

    	node = (dado*) malloc(sizeof(dado));

    	node = (*entrada)->first;

    	if(!node){
    		printf("Lista vazia!");
    		return FALHA;
    	}

    	while(node){

    		if(raizes[0].id == 0){
    			
    			raizes[0].id = 1;
    			
					int id;
				    int idYear;
				    int idTerm;
				    int idDay;
				    int idBeginSlot;
				    int idEndSlot;
				    Institution institutions[TAMANHO_MAX_DADOS];
				    int numInstitutions;
    			

    			printf("Amanhã iremos implantar alocação de memória.");


    		} else {

	    		A ser escrita, será verificado se há colisão do dado que está entrando com os que já estão inseridos na árvore
	    		
	    		int aux = checkEntrada(entrada, node);  	
				
				
    		}

    		

    		node = node->prox;
    	}

    	free(node);

*/