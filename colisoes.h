#ifndef _COLISOES_H_
#define _COLISOES_H_

#include "entradas.h"
#include "arvores.h"

void identificaPossivelColisao(Node** arvore,Dado** entrada, int tipoColisao);

void checarColisoesParciais(Dado** entrada, Node** raizes);

void checarColisoesTotais(Dado** entrada, Node** raiz);

#endif