#ifndef _COLISOES_H_
#define _COLISOES_H_

#include "entradas.h"
#include "arvores.h"

int calculaTempoColisao(Node** arvore,Dado** entrada, int nivelColisao);

void analisaAndGravaColisao(Node** arvore,Dado** entrada, int nivelColisao, int tipoColisao);

void identificaPossivelColisao(Node** arvore,Dado** entrada, int nivelColisao);

void checarColisoesParciais(Dado** entrada, Node** raizes);

void checarColisoesTotais(Dado** entrada, Node** raiz);

#endif