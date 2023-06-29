#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arvores.h"
#include "colisoes.h"

//Calcula o tamanho da colisão em minutos com base nos ids dos tempos de início e fim
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

//Compara as informações e grava os tipos de colisões
void analisaAndGravaColisao(Node** arvore,Dado** entrada, int nivelColisao, int tipoColisao){

	(*arvore)->dadosSolucao->solution.idCollisionType = tipoColisao;

	(*entrada)->solution.idCollisionType = tipoColisao;

	(*arvore)->dadosSolucao->solution.collisionLevel = nivelColisao;

	(*entrada)->solution.collisionLevel = nivelColisao;

	int tamanhoColisao = calculaTempoColisao(arvore,entrada,nivelColisao);

	//Grava o tempo de colisão, se houver outra com valor menor, não é salva
	(*arvore)->dadosSolucao->solution.collisionSize = (tamanhoColisao > (*arvore)->dadosSolucao->solution.collisionSize) ? tamanhoColisao : (*arvore)->dadosSolucao->solution.collisionSize;

	(*entrada)->solution.collisionSize = (tamanhoColisao > (*entrada)->solution.collisionSize) ? tamanhoColisao : (*entrada)->solution.collisionSize;

	//grava o dado de entrada no nó da árvore
	(*entrada)->solution.colisao = &((*arvore)->dadosSolucao->solution);

	//grava no dado de entrada o dado colidido
	(*arvore)->dadosSolucao->solution.colisao = &((*entrada)->solution);
	
}

//Percorre a árvore para comparar as informações (professor e sala)
void identificaPossivelColisao(Node** arvore,Dado** entrada, int nivelColisao){
	if ((*arvore) == NULL)
        return;

    int contador = 0;

    if((*arvore)->type == SOLUTION)
    	if(nivelColisao == PARCIAL){

    		//Colisão de professor
    		if((*arvore)->dadosSolucao->solution.idTeacher == (*entrada)->solution.idTeacher
    			&& (*arvore)->dadosSolucao->solution.idRoom != (*entrada)->solution.idRoom)
    				analisaAndGravaColisao(arvore,entrada,nivelColisao,COL_PROFESSOR);
    		
    		//Colisão de sala
    		if((*arvore)->dadosSolucao->solution.idTeacher != (*entrada)->solution.idTeacher
    			&& (*arvore)->dadosSolucao->solution.idRoom == (*entrada)->solution.idRoom)
    				analisaAndGravaColisao(arvore,entrada,nivelColisao,COL_SALA);

    		//Colisão de professor e sala
    		if((*arvore)->dadosSolucao->solution.idTeacher == (*entrada)->solution.idTeacher
    			&& (*arvore)->dadosSolucao->solution.idRoom == (*entrada)->solution.idRoom)
					analisaAndGravaColisao(arvore,entrada,nivelColisao,COL_PROF_SALA);
    	}
    

    if((*arvore)->type == SOLUTION)
    	if(nivelColisao == TOTAL)
    		if((*arvore)->id != (*entrada)->solution.id){

    			//Colisão de professor
    			if((*arvore)->dadosSolucao->solution.idTeacher == (*entrada)->solution.idTeacher
    			&& (*arvore)->dadosSolucao->solution.idRoom != (*entrada)->solution.idRoom)
    				analisaAndGravaColisao(arvore,entrada,nivelColisao,COL_PROFESSOR);
    		
    			//Colisão de sala
	    		if((*arvore)->dadosSolucao->solution.idTeacher != (*entrada)->solution.idTeacher
	    			&& (*arvore)->dadosSolucao->solution.idRoom == (*entrada)->solution.idRoom)
	    				analisaAndGravaColisao(arvore,entrada,nivelColisao,COL_SALA);

	    		//Colisão de professor e sala
	    		if((*arvore)->dadosSolucao->solution.idTeacher == (*entrada)->solution.idTeacher
	    			&& (*arvore)->dadosSolucao->solution.idRoom == (*entrada)->solution.idRoom)
						analisaAndGravaColisao(arvore,entrada,nivelColisao,COL_PROF_SALA);
    		}

    Node* proxNode = (*arvore);

    identificaPossivelColisao(&proxNode->child, entrada, nivelColisao);

    //A iteração não deve percorrer outras árvores, por isso retorna caso tente prosseguir para o irmão da raiz
    if(proxNode->brother != NULL)
    	if((proxNode->brother)->type == TIME)
    		return;

    identificaPossivelColisao(&proxNode->brother, entrada, nivelColisao);
}

//Percorre a lista de raízes para verificar se há um possível choque no tempo, se houver, checa se há colisão parcial
void checarColisoesParciais(Dado** entrada, Node** raizes){

	struct Dado* e = (*entrada);
	int aux = 0;

	Node* r = (*raizes);

	if(r->id == 0) {
		return;
	}

	while(r){

		//Se alguma informação sobre a data for divergente, não é necessária a verificação da colisão
		if(e->solution.idDay != (r->timeSet)->idDay || e->solution.idYear != (r->timeSet)->idYear || e->solution.idTerm != (r->timeSet)->idTerm){
			r = r->brother;
			continue;
		}

		//Caso em que a colisão é PARCIAL para a ENTRADA e TOTAL para a RAIZ
		if(((e->solution.idBeginSlot < (r->timeSet)->idBeginSlot) && (e->solution.idEndSlot ==  (r->timeSet)->idEndSlot)) || 
			((e->solution.idBeginSlot == (r->timeSet)->idBeginSlot) && (e->solution.idEndSlot > (r->timeSet)->idEndSlot)) ||
			((e->solution.idBeginSlot < (r->timeSet)->idBeginSlot) && (e->solution.idEndSlot > (r->timeSet)->idEndSlot))) {

			identificaPossivelColisao(&r,&e,PARCIAL);
		}

		//Caso em que a colisão é PARCIAL para a RAIZ e TOTAL para a ENTRADA
		if(((e->solution.idBeginSlot > (r->timeSet)->idBeginSlot) && (e->solution.idEndSlot == (r->timeSet)->idEndSlot)) ||
			((e->solution.idBeginSlot == (r->timeSet)->idBeginSlot) && (e->solution.idEndSlot < (r->timeSet)->idEndSlot)) ||
			((e->solution.idBeginSlot > (r->timeSet)->idBeginSlot) && (e->solution.idBeginSlot < (r->timeSet)->idEndSlot) && (e->solution.idEndSlot < (r->timeSet)->idEndSlot))) {

			identificaPossivelColisao(&r,&e,PARCIAL);

		}

		//Caso em que a colisão é PARCIAL para a ENTRADA e PARCIAL para a RAIZ
		if(((e->solution.idBeginSlot > (r->timeSet)->idBeginSlot) && (e->solution.idBeginSlot < (r->timeSet)->idEndSlot) && (e->solution.idEndSlot > (r->timeSet)->idEndSlot)) || 
			((e->solution.idBeginSlot < (r->timeSet)->idBeginSlot) && (e->solution.idEndSlot > (r->timeSet)->idBeginSlot) && (e->solution.idEndSlot < (r->timeSet)->idEndSlot))) {

			identificaPossivelColisao(&r,&e,PARCIAL);

		}

		r = r->brother;
	}
}

//Recebe o dado de entrada e a raiz que contém as soluções com os mesmos horários
void checarColisoesTotais(Dado** entrada, Node** raiz){
	identificaPossivelColisao(raiz,entrada,TOTAL);
}