#ifndef _ENTRADAS_H_
#define _ENTRADAS_H_

#define TAMANHO_MAX_STRING 1000
#define FALHA 0
#define SUCESSO 1

typedef struct {
    int id;
    int idSolution;
    char solutionName[TAMANHO_MAX_STRING];
    char solutionInitials[TAMANHO_MAX_STRING];
    int idTeacher;
    char teacherName[TAMANHO_MAX_STRING];
    int idDay;
    int idInstitution;
    int idUnit;
    char unitName[TAMANHO_MAX_STRING];
    int idUnitCourse;
    int idCourse;
    char courseName[TAMANHO_MAX_STRING];
    int idClass;
    char className[TAMANHO_MAX_STRING];
    int idDiscipline;
    char disciplineName[TAMANHO_MAX_STRING];
    int idRoom;
    char roomName[TAMANHO_MAX_STRING];
    int studentsNumber;
    int sequence;
    int idBeginSlot;
    char beginTimeName[TAMANHO_MAX_STRING];
    int idEndSlot;
    char endTimeName[TAMANHO_MAX_STRING];
    int idYear;
    int idTerm;
    int idCollisionType;
    int collisionLevel;
    int collisionSize;
    struct DadosEntrada* colisao;
} DadosEntrada;

DadosEntrada parseDadosEntrada(char *linha);

typedef struct Dado {
    unsigned int chave;
    DadosEntrada solution;
    struct Dado* ant;
    struct Dado* prox;
} Dado;

typedef struct noDescritor {
    struct Dado* first;
    struct Dado* last;
    int qtdDados;
} noDescritor;

int criarLista(noDescritor** noD);
int insOrdemRecebida(noDescritor** noD, DadosEntrada celula);
int lerDados(noDescritor** noD);
void printarDados(noDescritor** noD);

#endif