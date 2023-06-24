#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arvores.h"
#include "colisoes.h"

#define TOTAL 1024
#define PARCIAL 512

void verificaColisao(Node** arvore,Dado** entrada,Dado** lista, int tipoColisao){
	if ((*arvore) == NULL)
        return;

    if((*arvore)->type == SOLUTION){
    	printf("NÚMERO DA SOLUÇÃO: %d\n", (*arvore)->id);
    	printf("NÚMERO DA ENTRADA: %d\n\n", (*entrada)->solution.id);
    }

    Node* proxNode = (*arvore);

    verificaColisao(&proxNode->child, entrada, lista, tipoColisao);

    if(proxNode->brother != NULL)
    	if((proxNode->brother)->type == TIME)
    		return;

    verificaColisao(&proxNode->brother, entrada, lista, tipoColisao);
}

//IMPLEMENTAR
void checarColisoesParciais(Dado** entrada, Node** raizes, noDescritor** lista){

	struct Dado* e = (*entrada);
	struct Dado* l = (*lista)->first;
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

			verificaColisao(&r,&e,&l,PARCIAL);
		}

		//Caso em que a colisão é PARCIAL para a RAIZ e TOTAL para a ENTRADA  //1,6,7
		if(((e->solution.idBeginSlot > (r->timeSet)->idBeginSlot) && (e->solution.idEndSlot == (r->timeSet)->idEndSlot)) ||
			((e->solution.idBeginSlot == (r->timeSet)->idBeginSlot) && (e->solution.idEndSlot < (r->timeSet)->idEndSlot)) ||
			((e->solution.idBeginSlot > (r->timeSet)->idBeginSlot) && (e->solution.idBeginSlot < (r->timeSet)->idEndSlot) && (e->solution.idEndSlot < (r->timeSet)->idEndSlot))) {

			verificaColisao(&r,&e,&l,PARCIAL);

		}

		//Caso em que a colisão é PARCIAL para a ENTRADA e PARCIAL para a RAIZ //2,3
		if(((e->solution.idBeginSlot > (r->timeSet)->idBeginSlot) && (e->solution.idBeginSlot < (r->timeSet)->idEndSlot) && (e->solution.idEndSlot > (r->timeSet)->idEndSlot)) || 
			((e->solution.idBeginSlot < (r->timeSet)->idBeginSlot) && (e->solution.idEndSlot > (r->timeSet)->idBeginSlot) && (e->solution.idEndSlot < (r->timeSet)->idEndSlot))) {

			verificaColisao(&r,&e,&l,PARCIAL);

		}

		r = r->brother;
	}
}

//IMPLEMENTAR
void checarColisoesTotais(Dado** entrada, Node** raizes, noDescritor** lista){
	return;
}