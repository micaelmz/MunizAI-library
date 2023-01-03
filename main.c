#include <stdio.h>
#include "pandas.c"
#include "ai.c"

#define COLUNA_RESULTADO -1

int main() {
    // variaveis que armazenam as dimensoes do arquivo csv
    int len_lines = 0;
    int len_column = 0;

    int len_train = 0;
    int len_test = 0;

    // le o arquivo csv e armazena em uma matriz
    double **csv = read_csv("test.csv", &len_lines, &len_column);

    // divide o dataset em treino e teste
    double **train_data = malloc(len_lines * sizeof(double*));
    for (int i = 0; i < len_lines; i++) {
        train_data[i] = malloc(len_column * sizeof(double));
    }
    double **test_data = malloc(len_lines * sizeof(double*));
    for (int i = 0; i < len_lines; i++) {
        test_data[i] = malloc(len_column * sizeof(double));
    }

    train_test(csv, len_lines, 80, train_data, test_data, &len_train, &len_test);

    // separa as colunas do dataset de treino
    double *train_result = copy_column(train_data, len_lines, len_column, COLUNA_RESULTADO);
    double *test_result = copy_column(test_data, len_lines, len_column, COLUNA_RESULTADO);

    remove_column(csv, &len_lines, &len_column,COLUNA_RESULTADO);
    free(csv);

    // cria o perceptron
    Perceptron *p;

    int copy_len_column = len_column;
    int copy_len_test = len_test;

    // inicializa o perceptron
    fit(&p, 0.1, 1000, train_result, 16, train_data, len_column, len_train);

    predict(&p, test_data, copy_len_column, test_result, copy_len_test);
    printf("\n");
    system("pause");
    return 0;
}
