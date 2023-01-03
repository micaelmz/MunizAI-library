#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define MAX_LINE 9999

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
    printf("len_lines: %d, len_column: %d\n", *len_lines, *len_column);
    return matrix;
}


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
                printf("%f | ", csv[i][j]);
            }
            printf("\n");
        }
    }
}

void shuffle(double **matrix, int N, int M) {
    int *indices = malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        indices[i] = i;
    }

    srand(time(NULL)); // inicializa o gerador de números aleatórios
    for (int i = N - 1; i > 0; i--) {
        int j = rand() % (i + 1); // gera um índice aleatório entre 0 e i
        int temp = indices[i];
        indices[i] = indices[j];
        indices[j] = temp;
    }

    // Percorre o vetor de índices embaralhados e embaralha a matriz diretamente no ponteiro
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            double temp = matrix[i][j];
            matrix[i][j] = matrix[indices[i]][j];
            matrix[indices[i]][j] = temp;
        }
    }

    free(indices);
}

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
    printf("len_lines: %d, len_column: %d\n", *len_lines, *len_column);
    return new_csv;
}

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