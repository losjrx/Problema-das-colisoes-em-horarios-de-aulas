#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvores.h"
#include "entradas.h"

int numRaizes = 0;

Node* criaNovoNo(int tipoNo){

	Node* novo = (Node*)malloc(sizeof(Node));
	novo->id = 0;
	novo->type = tipoNo;
	novo->timeSet = NULL;
	novo->child = NULL;
	novo->brother = NULL;
	novo->numChildren = 0;
	novo->dadosSolucao = NULL;

	return(novo);
}

Node* inicializaArvores(int tipoNo){
	return(criaNovoNo(tipoNo));
}

//Escolhe a raiz onde será inserido o nó de acordo com as informações da variável timeSet (struct Time)
Node* escolheRaiz(Dado** entrada, Node** raizes){

	Node* rootAnterior;
	Node* novaRoot;
	Node* root = (*raizes);

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

	while(root){
		
		if((root->timeSet)->idYear == (*entrada)->solution.idYear && 
			(root->timeSet)->idTerm == (*entrada)->solution.idTerm && 
			(root->timeSet)->idDay == (*entrada)->solution.idDay && 
			(root->timeSet)->idBeginSlot == (*entrada)->solution.idBeginSlot && 
			(root->timeSet)->idEndSlot == (*entrada)->solution.idEndSlot)
		{
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

Node* verificaIdRaiz(Node** pai, int id){
	Node* aux = (*pai);
	if(aux->id == id){
		return aux;
	} else {
		Node* novaRaiz = criaNovoNo(id);
		novaRaiz->timeSet = aux->timeSet;
		novaRaiz->id = id;
		aux->brother = novaRaiz;
		return novaRaiz;
	}
}

//A partir da raiz de inserção, dado de entrada e o tipo do pai, busca-se o nó pai
Node* buscaPai(TIPOCHAVE chavePai, Dado** entrada, Node** raiz){
	if((*raiz) == NULL) 
		return FALHA;

	Node* aux = (*raiz);
	while(aux){
		if(aux->type == chavePai){ //se o tipo for o mesmo que o pai, retorna-se o endereço
			break;
		}
		aux = aux->child;

		//verificação dos irmãos do nós
		switch(aux->type){		
			case INSTITUTION: 	while(aux->id != (*entrada)->solution.idInstitution){
									aux = aux->brother;
								}
				break;								
			case SOLUTION: 		while(aux->id != (*entrada)->solution.id){
									aux = aux->brother;
								}
				break;
				default: break;
		}
	}

	if(!aux){
		printf("FALHA");
		return FALHA;
	}

	//verifica os ids e retorna o endereço
	if(aux->type == chavePai){
		switch(chavePai){
			case TIME: 
				return (*raiz);
			case INSTITUTION: 
				return verificaIdRaiz(&aux,(*entrada)->solution.idInstitution);
			case SOLUTION: 
				return verificaIdRaiz(&aux,(*entrada)->solution.id);
			default:
				return FALHA;
		}		
	}
}

//Verifica se o id do nó é igual ao nó de entrada
int verifiqueId(Node** p,Dado** entrada){
	switch((*p)->type){
		case INSTITUTION: if((*p)->id == (*entrada)->solution.idInstitution){ return SUCESSO;}
			break;
		case SOLUTION: if((*p)->id == (*entrada)->solution.id){ return SUCESSO;}
			break;
		default: return FALHA;
	}
	return FALHA;
}

//recebe a raiz de inserção e o dado de entrada, além de quem é o pai e o tipo da chave
Node* insere(Node** raiz, Dado** entrada, TIPOCHAVE novaChave, TIPOCHAVE chavePai){

	//Procura quem é o pai daquele novo nó dentro da árvore
	Node* pai = buscaPai(chavePai, entrada, raiz);

	if(!pai) 
		return NULL;

	Node* filho = criaNovoNo(novaChave);

	//todos os nós de uma mesma raiz possuem as informações de timeSet
	filho->timeSet = (*raiz)->timeSet;

	//inserindo as informações do nó, conforme o tipo
	switch(novaChave){
		case INSTITUTION: filho->id = (*entrada)->solution.idInstitution;
			break;
		case SOLUTION: 	filho->id = (*entrada)->solution.id;
						filho->dadosSolucao = (*entrada);	//O nó SOLUTION aguarda as informações da solução
			break;
		default:
			break;
	}

	//A partir daqui, tendo quem é o "pai" do nó, verifica se o novo será filho ou irmão dele
	Node* p = pai->child;


	if(!p){
		pai->child = filho;
		++(pai->numChildren);
	} else {
		while(p->brother) {
			if(verifiqueId(&p,entrada)){ //verifica se é o mesmo id (exemplo: mesma instituição), não sendo necessária a inserção
				free(filho);
				return p;
			}

			p = p->brother;
		}

		if(verifiqueId(&p,entrada)){
			free(filho);
			return p;
		}

		p->brother = filho;
	}

	return filho;
}

void exibirArvore(Node** raiz, int profundidade) {
    if ((*raiz) == NULL)
        return;

    for (int i = 0; i < profundidade; i++)
        printf("\t");

    switch ((*raiz)->type) {
        case TIME:
            printf("TIME: %d\n", (*raiz)->id);
            break;
        case INSTITUTION:
            printf("INSTITUTION: %d\n", (*raiz)->id);
            break;
        case SOLUTION:
            printf("SOLUTION: %d\n", (*raiz)->id);
            break;
        default:
            break;
    }

    Node* root = (*raiz);

    exibirArvore(&root->child, profundidade + 1);
    exibirArvore(&root->brother, profundidade);
}


Node* construirArvores(Dado** entrada, Node** raizes) {

	Node* aux;
	Node* raizDeInsercao;

	//retorna a raiz onde será inserido o nó
	raizDeInsercao = escolheRaiz(entrada,raizes);


	if(!raizDeInsercao){
		printf("Erro na escolha da raiz.");
        exit(1); 
	}

	//Insere o nó do tipo INSTITUTION, cujo pai é o TIME (raiz)
	aux = insere(&raizDeInsercao,entrada,INSTITUTION,TIME); if(!aux) return NULL;

	//Insere o nó do tipo SOLUTION, cujo pai é o INSTITUTION
	aux = insere(&raizDeInsercao,entrada,SOLUTION,INSTITUTION); if(!aux) return NULL;

    return raizDeInsercao;

}