#ifndef _ARVORES_H_
#define _ARVORES_H_

#include "entradas.h"

#define TIME 10
#define INSTITUTION 11
#define SOLUTION 100
#define ROOM 101
#define TEACHER 110
typedef int TIPOCHAVE;

typedef struct Time {
    int idYear;
    int idTerm;
    int idDay;
    int idBeginSlot;
    int idEndSlot;
} Time;

typedef struct Node {
    int id;
    int type;
    struct Time* timeSet;
    struct Node* child;
    struct Node* brother;
    int numChildren;
} Node;

Node* criaNovoNo(int TIPOCHAVE);

Node* inicializaArvores(int TIPOCHAVE);

Node* escolheRaiz(Dado** entrada, Node** raizes);

Node* buscaPai(TIPOCHAVE chavePai, Dado** entrada, Node** raiz);

int verifiqueId(TIPOCHAVE chavePai,Node** p,Dado** entrada);

Node* insere(Node** raiz, Dado** entrada, TIPOCHAVE novaChave, TIPOCHAVE chavePai);

void exibirArvore(Node** raiz, int profundidade);

int construirArvores(Dado** entrada, Node** raizes);

void checarColisoesParciais(Dado** entrada, Node** raizes, noDescritor** lista);

void checarColisoesTotais(Dado** entrada, Node** raizes, noDescritor** lista);

#endif