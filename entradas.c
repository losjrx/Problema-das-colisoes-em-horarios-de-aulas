#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "entradas.h"

//Grava os dados na strutc DadosEntrada
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

//aloca memória para o Nó Descritor
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

//Aloca memória para um novo nó da lista e o insere na ordem com a struct DadosEntrada na variável solution
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
                         (q->solution.idClass > atual->solution.idClass ||
                          (q->solution.idClass == atual->solution.idClass &&
                           (q->solution.idDay > atual->solution.idDay ||
                            (q->solution.idDay == atual->solution.idDay &&
                             q->solution.idBeginSlot > atual->solution.idBeginSlot))))))))))) {
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

//abre o arquivo de entrada e grava as informações na lista
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

    //Ignora primeira linha que contém nomes das variáveis.
    fgets(linha, sizeof(linha), file); 

    //Leitura dos dados de entrada
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


char* tipoDaColisao(int idCollisionType) {
    switch (idCollisionType) {
        case 1:
            return "Professor";
        case 2:
            return "Sala";
        case 3:
            return "Professor e Sala";
        default:
            return "Erro";
    }
}

char* nivelDaColisao(int collisionLevel) {
    switch (collisionLevel) {
        case 1:
            return ", parcial";
        case 2:
            return ", total";
        default:
            return "Erro";
    }
}

char* diaDaSemana(int idDay) {
    switch (idDay) {
        case 1:
            return "Dom";
        case 2:
            return "Seg";
        case 3:
            return "Ter";
        case 4:
            return "Qua";
        case 5:
            return "Qui";
        case 6:
            return "Sex";
        case 7:
            return "Sáb";
        default:
            return "Erro";
    }
}

//Grava as informações no arquivo de saída
void printarDados(noDescritor** noD, FILE* arquivo){
    struct Dado* q;

    q=(*noD)->first;

    int prevIdInstitution = -1;
    int prevIdUnit = -1;
    int prevIdCourse = -1;
    int prevIdClass = -1;

    while(q != NULL){

        if(q->solution.colisao == NULL){

            if(q->solution.idClass != prevIdClass){
               fprintf(arquivo, "\t\t\tTurma: %d\n", q->solution.idClass);
                prevIdClass = q->solution.idClass; 
            }
                
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

            fprintf(arquivo, "\t\t\t\t%s ", diaDaSemana(q->solution.colisao->idDay));
            fprintf(arquivo, "%c%c%c%c%c-", q->solution.colisao->beginTimeName[0],q->solution.colisao->beginTimeName[1],q->solution.colisao->beginTimeName[2],
                q->solution.colisao->beginTimeName[3],q->solution.colisao->beginTimeName[4],q->solution.colisao->beginTimeName[5]);
            fprintf(arquivo, "%c%c%c%c%c - ", q->solution.colisao->endTimeName[0],q->solution.colisao->endTimeName[1],q->solution.colisao->endTimeName[2],
                q->solution.colisao->endTimeName[3],q->solution.colisao->endTimeName[4],q->solution.colisao->endTimeName[5]);
            fprintf(arquivo, "%s%s -> [Instituição: %d, Unidade: %d, Curso: %d, Turma %d, Prof: %d, Sala: %d]\n", 
                tipoDaColisao(q->solution.idCollisionType), nivelDaColisao(q->solution.collisionLevel),
                q->solution.colisao->idInstitution, q->solution.colisao->idUnit, q->solution.colisao->idCourse, q->solution.colisao->idClass, 
                q->solution.colisao->idTeacher, q->solution.colisao->idRoom);

        }   

        q=q->prox;
    }
}