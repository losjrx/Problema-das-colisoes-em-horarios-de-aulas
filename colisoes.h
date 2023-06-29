#ifndef _COLISOES_H_
#define _COLISOES_H_

#include "entradas.h"
#include "arvores.h"

#define PARCIAL 1
#define TOTAL 2
#define COL_PROFESSOR 1
#define COL_SALA 2
#define COL_PROF_SALA 3

int calculaTempoColisao(Node** arvore,Dado** entrada, int nivelColisao);

void analisaAndGravaColisao(Node** arvore,Dado** entrada, int nivelColisao, int tipoColisao);

void identificaPossivelColisao(Node** arvore,Dado** entrada, int nivelColisao);

void checarColisoesParciais(Dado** entrada, Node** raizes);

void checarColisoesTotais(Dado** entrada, Node** raiz);

#endif