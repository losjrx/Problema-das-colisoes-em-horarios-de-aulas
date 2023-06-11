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

Node* buscaChave(TIPOCHAVE chave, Node** raiz){
	if((*raiz) == NULL) 
		return NULL;

	if((*raiz)->type == chave)
		return (*raiz);

	Node* p = (*raiz)->child;

	while(p) {
		Node* resp = buscaChave(chave, &p);
		if(resp) 
			return(resp);

		p = p->brother;
	}

	return(NULL);
}

Node* insere(Node** raiz, TIPOCHAVE novaChave, TIPOCHAVE chavePai){

	Node* pai = buscaChave(chavePai,raiz);

	if(!pai) 
		return(NULL);

	Node* filho = criaNovoNo(novaChave);

	Node* p = pai->child;

	if(!p){
		pai->child = filho;
		++(pai->numChildren);
	} else {
		while (p->brother){
			p = p->brother;
		}
		p->brother = filho;
	}

	return(filho);
}

void exibirArvore(Node** raiz){
	if((*raiz) == NULL) return;

	printf("%d(",(*raiz)->id);
	
	Node* p = (*raiz)->child;
	while (p) {
		exibirArvore(&p);
		p = p->brother;
	}
	printf(")");
}


int construirArvores(Dado** entrada, Node** raizes) {

	Node* aux;
	Node* raizDeInsercao;

	raizDeInsercao = escolheRaiz(entrada,raizes);


	if(!raizDeInsercao){
		printf("Erro na escolha da raiz.");
        exit(1); 
	}

	//VERIFICAR CODIGO

	aux = insere(&raizDeInsercao,INSTITUTION,TIME); if(!aux) return FALHA;
		aux->id = (*entrada)->solution.idInstitution;
		aux->timeSet = raizDeInsercao->timeSet;

	aux = insere(&raizDeInsercao,SOLUTION,INSTITUTION); if(!aux) return FALHA;
		aux->id = (*entrada)->solution.idSolution;
		aux->timeSet = raizDeInsercao->timeSet;

	aux = insere(&raizDeInsercao,ROOM,SOLUTION); if(!aux) return FALHA;
		aux->id = (*entrada)->solution.idRoom;
		aux->timeSet = raizDeInsercao->timeSet;

	aux = insere(&raizDeInsercao,TEACHER,ROOM); if(!aux) return FALHA;
		aux->id = (*entrada)->solution.idTeacher;
		aux->timeSet = raizDeInsercao->timeSet;

    return SUCESSO;

}