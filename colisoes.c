#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arvores.h"
#include "colisoes.h"

#define TOTAL 1024
#define PARCIAL 512

void analisaAndGravaColisao(Node** arvore,Dado** entrada, int tipoColisao){
	if(tipoColisao == TOTAL){
		printf("COLISÃO TOTAL\n");
		printf("NÚMERO DA SOLUÇÃO: %d\n", (*arvore)->id);
    	printf("NÚMERO DA ENTRADA: %d\n\n", (*entrada)->solution.id);
	} else {
		printf("COLISÃO PARCIAL\n");
		printf("NÚMERO DA SOLUÇÃO: %d\n", (*arvore)->id);
    	printf("NÚMERO DA ENTRADA: %d\n\n", (*entrada)->solution.id);
	}
}

void identificaPossivelColisao(Node** arvore,Dado** entrada, int tipoColisao){
	if ((*arvore) == NULL)
        return;

    if((*arvore)->type == SOLUTION)
    	if(tipoColisao == PARCIAL)
    		if((*arvore)->dadosSolucao->solution.idTeacher == (*entrada)->solution.idTeacher
    			|| (*arvore)->dadosSolucao->solution.idRoom == (*entrada)->solution.idRoom)
					analisaAndGravaColisao(arvore,entrada,tipoColisao);
    

    if((*arvore)->type == SOLUTION)
    	if(tipoColisao == TOTAL)
    		if((*arvore)->id != (*entrada)->solution.id)
    			if((*arvore)->dadosSolucao->solution.idTeacher == (*entrada)->solution.idTeacher
    			|| (*arvore)->dadosSolucao->solution.idRoom == (*entrada)->solution.idRoom)
					analisaAndGravaColisao(arvore,entrada,tipoColisao);
    

    Node* proxNode = (*arvore);

    identificaPossivelColisao(&proxNode->child, entrada, tipoColisao);

    if(proxNode->brother != NULL)
    	if((proxNode->brother)->type == TIME)
    		return;

    identificaPossivelColisao(&proxNode->brother, entrada, tipoColisao);
}

//IMPLEMENTAR
void checarColisoesParciais(Dado** entrada, Node** raizes){

	struct Dado* e = (*entrada);
	int aux = 0;

	Node* r = (*raizes);

	if(r->id == 0) {
		return;
	}

	while(r){

		if(e->solution.idDay != (r->timeSet)->idDay || e->solution.idYear != (r->timeSet)->idYear || e->solution.idTerm != (r->timeSet)->idTerm){
			r = r->brother;
			continue;
		}

		//Caso em que a colisão é PARCIAL para a ENTRADA e TOTAL para a RAIZ //4,5,8
		if(((e->solution.idBeginSlot < (r->timeSet)->idBeginSlot) && (e->solution.idEndSlot ==  (r->timeSet)->idEndSlot)) || 
			((e->solution.idBeginSlot == (r->timeSet)->idBeginSlot) && (e->solution.idEndSlot > (r->timeSet)->idEndSlot)) ||
			((e->solution.idBeginSlot < (r->timeSet)->idBeginSlot) && (e->solution.idEndSlot > (r->timeSet)->idEndSlot))) {

			identificaPossivelColisao(&r,&e,PARCIAL);
		}

		//Caso em que a colisão é PARCIAL para a RAIZ e TOTAL para a ENTRADA  //1,6,7
		if(((e->solution.idBeginSlot > (r->timeSet)->idBeginSlot) && (e->solution.idEndSlot == (r->timeSet)->idEndSlot)) ||
			((e->solution.idBeginSlot == (r->timeSet)->idBeginSlot) && (e->solution.idEndSlot < (r->timeSet)->idEndSlot)) ||
			((e->solution.idBeginSlot > (r->timeSet)->idBeginSlot) && (e->solution.idBeginSlot < (r->timeSet)->idEndSlot) && (e->solution.idEndSlot < (r->timeSet)->idEndSlot))) {

			identificaPossivelColisao(&r,&e,PARCIAL);

		}

		//Caso em que a colisão é PARCIAL para a ENTRADA e PARCIAL para a RAIZ //2,3
		if(((e->solution.idBeginSlot > (r->timeSet)->idBeginSlot) && (e->solution.idBeginSlot < (r->timeSet)->idEndSlot) && (e->solution.idEndSlot > (r->timeSet)->idEndSlot)) || 
			((e->solution.idBeginSlot < (r->timeSet)->idBeginSlot) && (e->solution.idEndSlot > (r->timeSet)->idBeginSlot) && (e->solution.idEndSlot < (r->timeSet)->idEndSlot))) {

			identificaPossivelColisao(&r,&e,PARCIAL);

		}

		r = r->brother;
	}
}

//IMPLEMENTAR
void checarColisoesTotais(Dado** entrada, Node** raiz){
	identificaPossivelColisao(raiz,entrada,TOTAL);
}