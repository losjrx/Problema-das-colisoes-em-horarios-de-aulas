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

    entrada.colisao = NULL;

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
    
    q=(Dado*)malloc(sizeof(Dado));
    if(q==NULL){printf("MEMORIA INSUFICIENTE\n"); return(FALHA);} else {
        
        (*noD)->qtdDados++;
        q->chave=(*noD)->qtdDados;
        q->solution=celula;
        
        if((*noD)->first==NULL){
            q->ant=NULL;
            q->prox=NULL;
            (*noD)->first=q;
            (*noD)->last=q;
        } else {
            struct Dado* atual = (*noD)->first;
            struct Dado* anterior = NULL;
            while (atual != NULL &&
                   (q->solution.idInstitution > atual->solution.idInstitution ||
                    (q->solution.idInstitution == atual->solution.idInstitution &&
                     (q->solution.idUnit > atual->solution.idUnit ||
                      (q->solution.idUnit == atual->solution.idUnit &&
                       (q->solution.idCourse > atual->solution.idCourse ||
                        (q->solution.idCourse == atual->solution.idCourse &&
                         q->solution.idClass > atual->solution.idClass))))))) {
                anterior = atual;
                atual = atual->prox;
            }
            if (anterior == NULL) {
                q->prox = (*noD)->first;
                ((*noD)->first)->ant = q;
                (*noD)->first = q;
            } else {
                anterior->prox = q;
                q->ant = anterior;
                q->prox = atual;
                if (atual != NULL) {
                    atual->ant = q;
                }
            }
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

void printarDados(noDescritor** noD, FILE* arquivo){
    struct Dado* q;

    q=(*noD)->first;

    int prevIdInstitution = -1;
    int prevIdUnit = -1;
    int prevIdCourse = -1;
    int prevIdClass = -1;

    while(q != NULL){

        if(q->solution.colisao == NULL){
            q=q->prox;
            continue;
        }


        if(q->solution.colisao != NULL){

            if (q->solution.idInstitution != prevIdInstitution){
                fprintf(arquivo, "Instituição: %d\n", q->solution.idInstitution);
                prevIdInstitution = q->solution.idInstitution;
            }

            if(q->solution.idUnit != prevIdUnit){
                fprintf(arquivo, "\tUnidade: %d\n", q->solution.idUnit);
                prevIdUnit = q->solution.idUnit;
            }
            
            if(q->solution.idCourse != prevIdCourse){
                fprintf(arquivo, "\t\tCurso: %d\n", q->solution.idCourse);
                prevIdCourse = q->solution.idCourse;

            }

            if(q->solution.idClass != prevIdClass){
                fprintf(arquivo, "\t\t\tTurma: %d\n", q->solution.idClass);
                prevIdClass = q->solution.idClass;

            }

            fprintf(arquivo, "\t\t\t\tColisao com solucao de id: %d\n", q->solution.colisao->id);


                
                   
            //q->solution.idClass,q->solution.colisao->idInstitution,q->solution.colisao->idUnit,q->solution.colisao->idCourse,q->solution.colisao->idClass;

        }   

        /*
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
        */

        q=q->prox;
    }
}