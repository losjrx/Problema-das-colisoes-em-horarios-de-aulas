#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "entradas.h"

DadosEntrada parseDadosEntrada(char *linha) {
    DadosEntrada entrada;
    sscanf(linha, "%d,%d,%[^,],%[^,],%d,%[^,],%d,%d,%d,%[^,],%d,%d,%[^,],%d,%[^,],%d,%[^,],%d,%[^,],%d,%d,%d,%[^,],%d,%[^,],%d,%d,%d,%d,%d",
           &entrada.id, &entrada.idSolution, entrada.solutionName, entrada.solutionInitials, &entrada.idTeacher, entrada.teacherName, &entrada.idDay,
           &entrada.idInstitution, &entrada.idUnit, entrada.unitName, &entrada.idUnitCourse, &entrada.idCourse, entrada.courseName, &entrada.idClass,
           entrada.className, &entrada.idDiscipline, entrada.disciplineName, &entrada.idRoom, entrada.roomName, &entrada.studentsNumber,
           &entrada.sequence, &entrada.idBeginSlot, entrada.beginTimeName, &entrada.idEndSlot, entrada.endTimeName, &entrada.idYear, &entrada.idTerm,
           &entrada.idCollisionType, &entrada.collisionLevel, &entrada.collisionSize);

    return entrada;
}

int criarLista(noDescritor** noD){
    noDescritor* q;
    
    q=(noDescritor*)malloc(sizeof(noDescritor));
    if(q==NULL){printf("MEMORIA INSUFICIENTE\n"); return(FALHA);}

    q->first = NULL;
    q->last = NULL;
    q->qtdDados = 0;
    (*noD) = q;

    return(SUCESSO);
}

int insOrdemRecebida(noDescritor** noD, DadosEntrada celula){

    struct Dado* q;
    struct Dado* r;
    
    q=(Dado*)malloc(sizeof(Dado));
    if(q==NULL){printf("MEMORIA INSUFICIENTE\n"); return(FALHA);} else {
        
        (*noD)->qtdDados++;
        q->chave=(*noD)->qtdDados;
        q->solution=celula;
        
        if((*noD)->first==NULL){
            q->prox=NULL;
            (*noD)->first=q;
            (*noD)->last=q;
        } else {
            q->prox=NULL;
            r=(*noD)->last;
            r->prox=q;
            (*noD)->last=q;
        }
    }
    return(SUCESSO);
}

int lerDados(noDescritor** noD){

    FILE *file = fopen("ColisaoHorarios-DadosEntrada.csv", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return FALHA;
    }

    int aux = criarLista(noD);
    if(!aux){
        printf("Erro na construção da lista.");
        exit(FALHA);
    }

    char linha[TAMANHO_MAX_STRING];

    fgets(linha, sizeof(linha), file); //ignora primeira linha que contém nomes das variáveis.

    while (fgets(linha, sizeof(linha), file) != NULL) {

        DadosEntrada entrada = parseDadosEntrada(linha);
        aux = insOrdemRecebida(noD, entrada);

        if(!aux){
            printf("Erro na construção da lista.");
            exit(1);
        }
    }

    fclose(file);

    return SUCESSO;
}

void printarDados(noDescritor** noD){
    struct Dado* q;

    q=(*noD)->first;

    while(q != NULL){

        printf("id: %d\n", q->solution.id);
        printf("idSolution: %d\n", q->solution.idSolution);
        printf("solutionName: %s\n", q->solution.solutionName);
        printf("solutionInitials: %s\n", q->solution.solutionInitials);
        printf("idTeacher: %d\n", q->solution.idTeacher);
        printf("teacherName: %s\n", q->solution.teacherName);
        printf("idDay: %d\n", q->solution.idDay);
        printf("idInstitution: %d\n", q->solution.idInstitution);
        printf("idUnit: %d\n", q->solution.idUnit);
        printf("unitName: %s\n", q->solution.unitName);
        printf("idUnitCourse: %d\n", q->solution.idUnitCourse);
        printf("idCourse: %d\n", q->solution.idCourse);
        printf("courseName: %s\n", q->solution.courseName);
        printf("idClass: %d\n", q->solution.idClass);
        printf("className: %s\n", q->solution.className);
        printf("idDiscipline: %d\n", q->solution.idDiscipline);
        printf("disciplineName: %s\n", q->solution.disciplineName);
        printf("idRoom: %d\n", q->solution.idRoom);
        printf("roomName: %s\n", q->solution.roomName);
        printf("studentsNumber: %d\n", q->solution.studentsNumber);
        printf("sequence: %d\n", q->solution.sequence);
        printf("idBeginSlot: %d\n", q->solution.idBeginSlot);
        printf("beginTimeName: %s\n", q->solution.beginTimeName);
        printf("idEndSlot: %d\n", q->solution.idEndSlot);
        printf("endTimeName: %s\n", q->solution.endTimeName);
        printf("idYear: %d\n", q->solution.idYear);
        printf("idTerm: %d\n", q->solution.idTerm);
        printf("idCollisionType: %d\n", q->solution.idCollisionType);
        printf("collisionLevel: %d\n", q->solution.collisionLevel);
        printf("collisionSize: %d\n", q->solution.collisionSize);
        printf("\n");

        q=q->prox;
    }
}

Dado* encontraDado(int idSolution, noDescritor** noD){
    Dado* q = (*noD)->first;

    while(q->solution.idSolution != idSolution){
        q = q->prox;
    }

    return q;
}