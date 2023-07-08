# Problema-das-colisoes-em-horarios-de-aulas
Desenvolvimento de uma aplicação que, a partir de um conjunto de dados C (previamente fornecido e num formato especial), seja ela capaz de apresentar uma “árvore de colisões” (ou árvore de conflitos), possibilitando ao usuário da aplicação, de maneira rápida, identificar em que “locais” o horário de aulas está inconsistente.

### Compilação

Para compilar o código em C, pode-se utilizar o compilador gcc. O compilador é responsável por traduzir o código fonte escrito em uma linguagem específica para um arquivo que o computador saiba interpretar, ou seja, um executável. No terminal, basta digitar no diretório que contém os códigos:

>gcc -o executavel principal.c entradas.c arvores.c colisoes.c

### Dados de entrada

O conjunto de dados de entrada é representado por um arquivo do tipo CSV (Comma Separated Values).

Em cada da linha contém as seguintes informações, nesta ordem:

1. **id** – número inteiro e estritamente positivo (NIEP), chave primária de C
2. **idSolution **– NIEP, uma chave secundária de C
3. **solutionName** – uma cadeia de caracteres, não vazia, que representa um nome, ou descrição, dado para a solução;
4. **solutionInitials** – uma cadeia de caracteres, não vazia, que representa uma abreviatura – normalmente um acrônimo – para a solução;
5. **idTeacher** – NIEP, chave primária em relação a C. Ou seja: dois professores nunca terão o mesmo“id”;
6. **teacherName** – uma cadeia de caracteres, não vazia, com o nome do professor;
7. **idDay** – NIEP [1 - dom, 2 - seg, 3 - ter, ..., 7 - sáb];
8. **idInstitution** – NIEP, chave primária em relação a C. Ou seja: duas instituições nunca terão o mesmo “id”;
9. **idUnit** – NIEP, chave primária em relação à instituição. Ou seja: numa determinada instituição, duas unidades nunca terão o mesmo “id”;
10. **unitName** – uma cadeia de caracteres, não vazia, que representa um nome, ou descrição, dado para a unidade;
11. **idUnitCourse** – NIEP, denota a relação de um curso com a sua unidade acadêmica mas que, nesta aplicação, não precisará ser processado;
12. **idCourse** – NIEP, chave primária em relação à instituição/unidade. Ou seja: numa determinada instituição e unidade, dois cursos nunca terão o mesmo “id”;
13. **courseName** – uma cadeia de caracteres, não vazia, que representa um nome, ou descrição, dado para o curso;
14. **idClass** – NIEP, chave primária em relação à instituição/unidade. Ou seja: numa determinada instituição e unidade, duas turmas nunca terão o mesmo “id”;
15. **className** – uma cadeia de caracteres, não vazia, que representa um nome, ou descrição, dado para a turma;
16. **idDiscipline** – NIEP, chave primária em relação a C. Ou seja: duas disciplinas nunca terão o mesmo “id”;
17. **disciplineName** – uma cadeia de caracteres, não vazia, que representa um nome, ou descrição, dado para a disciplina;
18. **idRoom** – NIEP, chave primária em relação à instituição. Ou seja: numa determinada instituição, duas salas nunca terão o mesmo “id”;
19. **roomName** – uma cadeia de caracteres, não vazia, que representa um nome, ou descrição, dado para a sala;
20. **studentsNumber** – NIEP, número de estudantes que está matriculado naquela disciplina;
21. **sequence** – NIEP, indica a posição ocupada, numa sequência de séries e/ou períodos, por aquele disciplina na matriz curricular do curso ao qual a turma está vinculada. Por exemplo: 1 = 1º período, 2 = 2º período, : : : , 10 = 10º período;
22. **idBeginSlot** – NIEP, número da posição, numa ordem sequencial iniciada em 0 (zero), que corresponde a um determinado intervalo de tempo no qual o dia for dividido. Por exemplo, considerando que o dia seja dividido em intervalos de tempo de 15min, então o horário das 00 : 00 : 00 às 00 : 14 : 59 corresponde ao “id” 0 (zero), o horário das 00 : 15 : 00 às 00 : 29 : 59 ao “id” 1 e, assim, sucessivamente, até que o horário das 23 : 45 : 00 às 23 : 59 : 59 corresponda ao “id” 95, pois o dia foi dividido em 96 intervalos de tempo, numerados sequencialmente de 0 a 95;
23. **beginTimeName** – uma cadeia de caracteres, não vazia, no formato “hh:mm:ss”, que corresponde ao horário de início de intervalo de tempo corresponde a idBeginSlot;(24) idEndSlot – NIEP
25. **endTimeName** – uma cadeia de caracteres, não vazia, no formato “hh:mm:ss”, que corresponde ao horário de início de intervalo de tempo corresponde a idEndSlot;
26. **idYear** – NIEP, correspondente ao ano;
27. **idTerm** – NIEP, correspondente ao semestre letivo [1 - 1º semestre, 2º - semestre];
28. **idCollisionType** – número inteiro positivo que, inicialmente, estará com o valor 0 e que deverá ser atualizado pela aplicação ao gerar o arquivo de saída. Ele corresponde ao tipo de colisão que correu com esta aula, sendo:
(0) – nenhuma colição ocorreu;
(1) – colisão de professor, ou seja, o professor de “id” igual a idTeacher está associado a uma outra aula cujo horário coincide, parcial ou totalmente, a horário da aula presente;
(2) – colisão de sala de aula, ou seja, a sala de aula de “id” igual a idRoom está sendo utilizada por uma outra aula, neste mesmo intervalo de tempo ou em pelo menos parte dele;
(3) – colisão de professor e de sala, ou seja, as colisões do tipo (1) e (2) estão ocorrendo simultaneamente.
29. **collisionLevel** – número inteiro positivo que, inicialmente, estará com o valor 0 e que deverá ser atualizado pela aplicação ao gerar o arquivo de saída. Ele corresponde ao nível da colisão que ocorreu com a presente aula, sendo:
(0) – nenhuma colisão ocorreu;
(1) – colisão parcial, ou seja, existe uma outra aula cujo intervalo de tempo é coincidente, parcialmente, com o horário da presente aula;
(2) – colisão total, ou seja, existe uma outra aula cujo intervalo de tempo é totalmente coincidente com o horário da presente aula.
30. **collisionSize** – número inteiro positivo que, inicialmente, estará com o valor 0 e que deverá ser atualizado pela aplicação ao gerar o arquivo de saída. Corresponde à quantidade de tempo, expressa em minutos, em que está ocorrendo a colisão. Se a colisão for do tipo (3) [idCollisionType = 3], considere a colisão de maior duração. 

>Por exemplo, uma linha de linha típica do arquivo do conjunto de entrada C é: 126, 1001, ’Solução base n. 001’, ’SB-001’, 101, ’Alan Mathison Turing’, 2, 900, 1, ’INF/UFG’, 1, 1, ’BSI’, 3, ’BSI-03’, 1001, ’AED-2’, 305, ’Sala 305’, 55, 3, 75, ’18:45:00’, 88, ’22:00:00’, 2023, 1, 0, 0, 0


### Arquivo de saída

É gerado o arquivo de saída saidas.txt, com as informações somente dos horários em que houve algum tipo de colisão.
