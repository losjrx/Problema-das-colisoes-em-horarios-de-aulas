#ifndef _COLISOES_H_
#define _COLISOES_H_

#define TAMANHO_MAX_STRING 500
#define ERRO -1
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
    int idDisciplinha;
    char disciplinhaName[TAMANHO_MAX_STRING];
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
} DadosEntrada;

DadosEntrada parseDadosEntrada(char *linha);

#endif