#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arvores.h"
#include "colisoes.h"

#define PARCIAL 1
#define TOTAL 2
#define COL_PROFESSOR 1
#define COL_SALA 2
#define COL_PROF_SALA 3

int calculaTempoColisao(Node** arvore,Dado** entrada, int nivelColisao){
	if(nivelColisao == TOTAL){
		return ((*entrada)->solution.idEndSlot-(*entrada)->solution.idBeginSlot)*30;
	}

	int begin1 = (*entrada)->solution.idBeginSlot;
	int end1 = (*entrada)->solution.idEndSlot;

	int begin2 = (*arvore)->dadosSolucao->solution.idBeginSlot;
	int end2 = (*arvore)->dadosSolucao->solution.idEndSlot;

	int intervaloComum = 0;

	if ((begin1 <= end2) && (end1 >= begin2)) {
        int start = (begin1 > begin2) ? begin1 : begin2;
        int end = (end1 < end2) ? end1 : end2;
        intervaloComum = end - start;
    }

	return intervaloComum*30;

}

void analisaAndGravaColisao(Node** arvore,Dado** entrada, int nivelColisao, int tipoColisao){

	(*arvore)->dadosSolucao->solution.idCollisionType = tipoColisao;

	(*entrada)->solution.idCollisionType = tipoColisao;

	(*arvore)->dadosSolucao->solution.collisionLevel = nivelColisao;

	(*entrada)->solution.collisionLevel = nivelColisao;

	int tamanhoColisao = calculaTempoColisao(arvore,entrada,nivelColisao);

	(*arvore)->dadosSolucao->solution.collisionSize = (tamanhoColisao > (*arvore)->dadosSolucao->solution.collisionSize) ? tamanhoColisao : (*arvore)->dadosSolucao->solution.collisionSize;

	(*entrada)->solution.collisionSize = (tamanhoColisao > (*entrada)->solution.collisionSize) ? tamanhoColisao : (*entrada)->solution.collisionSize;

	if(nivelColisao == TOTAL){
		printf("COLISAO TOTAL\n");
		printf("NUMERO DA SOLUCAO: %d\n", (*arvore)->id);
    	printf("NUMERO DA ENTRADA: %d\n", (*entrada)->solution.id);
    	printf("TIPO DE COLISAO: %d\n", tipoColisao);
    	printf("NIVEL DE COLISAO: %d\n", nivelColisao);
    	printf("TAMANHO DA COLISAO EM MINUTOS: %d\n\n", tamanhoColisao);
	} 

	if(nivelColisao == PARCIAL){
		printf("COLISAO PARCIAL\n");
		printf("NUMERO DA SOLUCAO: %d\n", (*arvore)->id);
    	printf("NUMERO DA ENTRADA: %d\n", (*entrada)->solution.id);
    	printf("TIPO DE COLISAO: %d\n", tipoColisao);
    	printf("NIVEL DE COLISAO: %d\n", nivelColisao);
    	printf("TAMANHO DA COLISAO EM MINUTOS: %d\n\n", tamanhoColisao);
	}
	
}

void identificaPossivelColisao(Node** arvore,Dado** entrada, int nivelColisao){
	if ((*arvore) == NULL)
        return;

    int contador = 0;

    if((*arvore)->type == SOLUTION)
    	if(nivelColisao == PARCIAL){

    		if((*arvore)->dadosSolucao->solution.idTeacher == (*entrada)->solution.idTeacher
    			&& (*arvore)->dadosSolucao->solution.idRoom != (*entrada)->solution.idRoom)
    				analisaAndGravaColisao(arvore,entrada,nivelColisao,COL_PROFESSOR);
    		

    		if((*arvore)->dadosSolucao->solution.idTeacher != (*entrada)->solution.idTeacher
    			&& (*arvore)->dadosSolucao->solution.idRoom == (*entrada)->solution.idRoom)
    				analisaAndGravaColisao(arvore,entrada,nivelColisao,COL_SALA);

    		if((*arvore)->dadosSolucao->solution.idTeacher == (*entrada)->solution.idTeacher
    			&& (*arvore)->dadosSolucao->solution.idRoom == (*entrada)->solution.idRoom)
					analisaAndGravaColisao(arvore,entrada,nivelColisao,COL_PROF_SALA);
    	}
    

    if((*arvore)->type == SOLUTION)
    	if(nivelColisao == TOTAL)
    		if((*arvore)->id != (*entrada)->solution.id){

    			if((*arvore)->dadosSolucao->solution.idTeacher == (*entrada)->solution.idTeacher
    			&& (*arvore)->dadosSolucao->solution.idRoom != (*entrada)->solution.idRoom)
    				analisaAndGravaColisao(arvore,entrada,nivelColisao,COL_PROFESSOR);
    		

	    		if((*arvore)->dadosSolucao->solution.idTeacher != (*entrada)->solution.idTeacher
	    			&& (*arvore)->dadosSolucao->solution.idRoom == (*entrada)->solution.idRoom)
	    				analisaAndGravaColisao(arvore,entrada,nivelColisao,COL_SALA);

	    		if((*arvore)->dadosSolucao->solution.idTeacher == (*entrada)->solution.idTeacher
	    			&& (*arvore)->dadosSolucao->solution.idRoom == (*entrada)->solution.idRoom)
						analisaAndGravaColisao(arvore,entrada,nivelColisao,COL_PROF_SALA);
    		}

    Node* proxNode = (*arvore);

    identificaPossivelColisao(&proxNode->child, entrada, nivelColisao);

    if(proxNode->brother != NULL)
    	if((proxNode->brother)->type == TIME)
    		return;

    identificaPossivelColisao(&proxNode->brother, entrada, nivelColisao);
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