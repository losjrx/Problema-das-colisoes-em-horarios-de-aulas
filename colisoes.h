#ifndef _COLISOES_H_
#define _COLISOES_H_

#include "entradas.h"
#include "arvores.h"

void verificaColisao(Node** arvore,Dado** entrada,Dado** lista, int tipoColisao);

void checarColisoesParciais(Dado** entrada, Node** raizes, noDescritor** lista);

void checarColisoesTotais(Dado** entrada, Node** raizes, noDescritor** lista);

#endif