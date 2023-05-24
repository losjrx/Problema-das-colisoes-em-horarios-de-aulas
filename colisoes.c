#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "colisoes.h"

DadosEntrada parseDadosEntrada(char *linha) {
    DadosEntrada entrada;
    sscanf(linha, "%d, %d, '%[^']', '%[^']', %d, '%[^']', %d, %d, %d, '%[^']', %d, %d, '%[^']', %d, '%[^']', %d, '%[^']', %d, '%[^']', %d, %d, %d, '%[^']', %d, '%[^']', %d, %d, %d, %d, %d",
           &entrada.id, &entrada.idSolution, entrada.solutionName, entrada.solutionInitials, &entrada.idTeacher, entrada.teacherName, &entrada.idDay,
           &entrada.idInstitution, &entrada.idUnit, entrada.unitName, &entrada.idUnitCourse, &entrada.idCourse, entrada.courseName, &entrada.idClass,
           entrada.className, &entrada.idDisciplinha, entrada.disciplinhaName, &entrada.idRoom, entrada.roomName, &entrada.studentsNumber,
           &entrada.sequence, &entrada.idBeginSlot, entrada.beginTimeName, &entrada.idEndSlot, entrada.endTimeName, &entrada.idYear, &entrada.idTerm,
           &entrada.idCollisionType, &entrada.collisionLevel, &entrada.collisionSize);

    return entrada;
}

int main() {
    
    FILE *file = fopen("dados.csv", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    char linha[TAMANHO_MAX_STRING];
    while (fgets(linha, sizeof(linha), file) != NULL) {
        DadosEntrada entrada = parseDadosEntrada(linha);

        // Faça o que precisa ser feito com os dados da linha
        // Exemplo de impressão dos dados:
        printf("id: %d\n", entrada.id);
        printf("idSolution: %d\n", entrada.idSolution);
        printf("solutionName: %s\n", entrada.solutionName);
        printf("solutionInitials: %s\n", entrada.solutionInitials);
        printf("idTeacher: %d\n", entrada.idTeacher);
        printf("teacherName: %s\n", entrada.teacherName);
        printf("idDay: %d\n", entrada.idDay);
        printf("idInstitution: %d\n", entrada.idInstitution);
        printf("idUnit: %d\n", entrada.idUnit);
        printf("unitName: %s\n", entrada.unitName);
        printf("idUnitCourse: %d\n", entrada.idUnitCourse);
        printf("idCourse: %d\n", entrada.idCourse);
        printf("courseName: %s\n", entrada.courseName);
        printf("idClass: %d\n", entrada.idClass);
        printf("className: %s\n", entrada.className);
        printf("idDisciplinha: %d\n", entrada.idDisciplinha);
        printf("disciplinhaName: %s\n", entrada.disciplinhaName);
        printf("idRoom: %d\n", entrada.idRoom);
        printf("roomName: %s\n", entrada.roomName);
        printf("studentsNumber: %d\n", entrada.studentsNumber);
        printf("sequence: %d\n", entrada.sequence);
        printf("idBeginSlot: %d\n", entrada.idBeginSlot);
        printf("beginTimeName: %s\n", entrada.beginTimeName);
        printf("idEndSlot: %d\n", entrada.idEndSlot);
        printf("endTimeName: %s\n", entrada.endTimeName);
        printf("idYear: %d\n", entrada.idYear);
        printf("idTerm: %d\n", entrada.idTerm);
        printf("idCollisionType: %d\n", entrada.idCollisionType);
        printf("collisionLevel: %d\n", entrada.collisionLevel);
        printf("collisionSize: %d\n", entrada.collisionSize);
        printf("\n");
    }

    fclose(file);
    return 0;
}