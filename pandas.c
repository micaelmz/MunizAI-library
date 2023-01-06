#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LINE 9999

// Check if a float is an integer.
// Input: num = number.
int is_float(float num){
    if (num == (int)num){
        return 0;
    }else{
        return 1;
    }
}

// Lê um arquivo .csv e retorna uma matriz com os dados float..
// Entradas: filename = nome do arquivo .csv, len_lines = ponteiro para a variavel que armazenará o numero de linhas do arquivo, len_column = ponteiro para a variavel que armazenará o numero de colunas do arquivo.
double **read_csv(const char *filename, int *len_lines, int *len_column) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error while opening the file %s\n", filename);
        exit(1);
    }

    double **matrix = NULL;
    char line[MAX_LINE];
    while (fgets(line, MAX_LINE, fp) != NULL) {
        *len_lines += 1;
        matrix = realloc(matrix, (*len_lines) * sizeof(double *));

        // Find the end of the line
        char *newline = strchr(line, '\n');
        if (newline) {
            *newline = '\0';
        }

        // Make a copy of the line to use with strtok
        char line_copy[MAX_LINE];
        strcpy(line_copy, line);

        // Reset len_column for the current line
        *len_column = 0;

        // Conta o número de colunas da linha atual
        char *token = strtok(line_copy, ",");
        while (token != NULL) {
            *len_column += 1;
            token = strtok(NULL, ",");
        }
        // Aloca um vetor para armazenar os dados da linha atual
        matrix[*len_lines - 1] = malloc(*len_column * sizeof(double));

        // Lê os dados da line e armazena na matrix
        token = strtok(line, ",");
        int i = 0;
        while (token != NULL) {
            matrix[*len_lines - 1][i++] = atof(token);
            token = strtok(NULL, ",");
        }
        // Resize the memory block to the actual number of elements in the line
        matrix[*len_lines - 1] = realloc(matrix[*len_lines - 1], i * sizeof(double));
    }
    fclose(fp);

    // ------ PRE SETTINGS FOR THE PRINTS ------
    int limiter = 0; int index_space = 1;
    int columns_space[*len_column];

    for (int i = 0; i < *len_column; i++){
        columns_space[i] = 3;
    }

    // define the limiter
    if (*len_lines < 5)
        limiter = *len_lines;
    else
        limiter = 5;

    // define the index limiter
    int num = *len_lines;
    while (num > 10) {
        num /= 10;
        index_space = index_space + 1;
    }

    // define the columns limiter
    for (int i = 0; i < *len_lines; i++){
        for (int j = 0; j < *len_column; j++){
            num = matrix[i][j];
            int space = 1;
            while (num > 10) {
                num /= 10;
                space = space + 1;
            }
            if (space > columns_space[j])
                columns_space[j] = space;
        }
    }

    // ------ PRINTS ------
    for (int i = 0; i < limiter; i++) {
        printf("%-*d  ", index_space, i);
        for (int j = 0; j < *len_column; j++) {
            if (is_float(matrix[i][j])){
                printf("%*.2f  ", columns_space[j], matrix[i][j]);
            }
            else{
                printf("%*.0f  ", columns_space[j], matrix[i][j]);
            }
        }
        printf("\n");
    }

    for (int i = 0; i < *len_column; i++){
        if (is_float(matrix[limiter][i])){
            // TODO - This if isnt 100% right, because it's only checking the first number after the limiter, should check all the numbers after the limiter.
            if (matrix[limiter][i] >= 10)
                printf("%-*s  ", columns_space[i]+2, "...");
            else
                printf("%-*s  ", columns_space[i]+1, "...");
        }
        else{
            printf("%*s  ", columns_space[i], "...");
        }
    }

    printf("\n");

    for (int i = *len_lines - 5; i < *len_lines; i++) {
        printf("%-*d  ", index_space, i);
        for (int j = 0; j < *len_column; j++) {
            if (is_float(matrix[i][j])){
                printf("%*.2f  ", columns_space[j], matrix[i][j]);
            }
            else{
                printf("%*.0f  ", columns_space[j], matrix[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n[%d rows x %d columns]\n", *len_lines, *len_column);
    return matrix;

    // TODO - refactor this function, it's too big, it's possible to separate the prints in another function. (will be userfull to for the other functions)
}

// Imprime a matriz do csv em um formato semelhante ao pandas
// Entradas: csv = matriz com os dados do arquivo csv, len_lines = numero de linhas da matriz, len_column = numero de colunas da matriz
void print_csv(double **csv, int len_lines, int len_column) {
    int i = 0;
    if (len_column == 1) {
        for (i = 0; i < len_lines; i++) {
            printf("%d| %f |",i, csv[i]);
            printf("\n");
        }
    }else{
        for (int i = 0; i < len_lines; i++) {
            printf("%d| ", i);
            for (int j = 0; j < len_column; j++) {
                printf("%.2f| ", csv[i][j]);
            }
            printf("\n");
        }
    }
}

// Embaralha as linhas da matriz do csv
// Entradas: csv = matriz com os dados do arquivo csv, len_lines = numero de linhas da matriz, len_column = numero de colunas da matriz
void shuffle(double **matrix, int len_lines, int len_column) {
    int *index = malloc(len_lines * sizeof(int));
    for (int i = 0; i < len_lines; i++) {
        index[i] = i;
    }

    srand(time(NULL));
    for (int i = len_lines - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = index[i];
        index[i] = index[j];
        index[j] = temp;
    }

    // Percorre o vetor de índices embaralhados e embaralha a matriz diretamente no ponteiro
    for (int i = 0; i < len_lines; i++) {
        for (int j = 0; j < len_column; j++) {
            double temp = matrix[i][j];
            matrix[i][j] = matrix[index[i]][j];
            matrix[index[i]][j] = temp;
        }
    }

    free(index);
}

// Remove uma coluna da matriz do csv
// Entradas csv = matriz com os dados do arquivo csv, len_lines = numero de linhas da matriz, len_column = numero de colunas da matriz, column = coluna a ser removida
double **remove_column(double **csv, int *len_lines, int *len_column, int column) {
    if (column >= *len_column) {
        printf("Error: column %d is out of range\n", column);
        exit(1);
    }

    if (column < 0){
        column = *len_column - column;
    }

    double **new_csv = malloc(*len_lines * sizeof(double *));

    for (int i = 0; i < *len_lines; i++) {
        new_csv[i] = malloc((*len_column - 1) * sizeof(double));
        int j = 0;
        for (int k = 0; k < *len_column; k++) {
            if (k != column) {
                new_csv[i][j++] = csv[i][k];
            }
        }
    }

    *len_column -= 1;
    //printf("len_lines: %d, len_column: %d\n", *len_lines, *len_column);
    return new_csv;
}

// Copia uma coluna da matriz do csv
// Entradas csv = matriz com os dados do arquivo csv, len_lines = numero de linhas da matriz, len_column = numero de colunas da matriz, column = coluna a ser copiada
double *copy_column(double **csv, int len_lines, int len_column, int column) {
    if (column >= len_column) {
        printf("Error: column %d is out of range\n", column);
        exit(1);
    }
    if (column < 0){
        column = len_column + column;
    }
    double *new_column = malloc(len_lines * sizeof(double));
    for (int i = 0; i < len_lines; i++) {
        new_column[i] = csv[i][column];
    }
    return new_column;
}

    // TODO - HEAD the head function of pandas