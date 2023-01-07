#include <stdio.h>
#include <stdlib.h>
#include "pandas.c"
#include "perceptron.c"

int main() {
    // Variaveis que armazenam as dimensoes do arquivo csv
    int len_lines = 0; int len_column = 0; int len_train = 0; int len_test = 0;

    // Columna onde está o resultado binario da classificação
    int RESULT_COLUMN = NULL;

    // EXEMPLO 1 - Perceptron:
    // Predição se uma empresa vai falir ou não, baseado em 94 indicadores.
    // Créditos do Dataset: https://www.kaggle.com/datasets/fedesoriano/company-bankruptcy-prediction?resource=download
    // Remova o comentário de bloco abaixo para utilizar o exemplo 1.
    /*
    // Define a última coluna como a coluna de resultado
    RESULT_COLUMN = 0;

    // Carrega o dataset
    double **csv = read_csv("dataset-examples/bankruptcy.csv", &len_lines, &len_column);

    // Embaralha o dataset (opcional, recomendo NÃO USAR neste exemplo)
    //shuffle(dataset, len_lines, len_column);

    // Aloca as matrizes de treino e teste
    double **train_data = malloc(len_lines * sizeof(double*));
    for (int i = 0; i < len_lines; i++) {
        train_data[i] = malloc(len_column * sizeof(double));
    }
    double **test_data = malloc(len_lines * sizeof(double*));
    for (int i = 0; i < len_lines; i++) {
        test_data[i] = malloc(len_column * sizeof(double));
    }

    // Divide o dataset em treino e teste
    train_test(csv, len_lines, 80, train_data, test_data, &len_train, &len_test);

    // Separa ambos datasets de treino e teste em dados e resultados.
    double *train_result = copy_column(train_data, len_lines, len_column, RESULT_COLUMN);
    double *test_result = copy_column(test_data, len_lines, len_column, RESULT_COLUMN);

    remove_column(csv, &len_lines, &len_column,RESULT_COLUMN);
    free(csv);

    // Cria a rede neural (Perceptron)
    Perceptron *p;

    // Devido a um bug de ponteiros, é necessário fazer um backup do tamanho do dataset de teste e a quantidade de colunas (após o treino ele fica com valores aleatorios)
    int copy_len_column = len_column;
    int copy_len_test = len_test;

    // Treina a rede neural com o dataset de treino, utilizando o Perceptron
    fit(&p, 0.1, 500, 16, train_data, train_result, len_column, len_train);

    // Testa a rede neural com o dataset de teste
    predict(&p, test_data, test_result, copy_len_column, copy_len_test);
    */

    // EXEMPLO 2 - Perceptron:
    // Predição de se um paciente tem ou não diabetes.
    // Créditos do Dataset: https://www.kaggle.com/uciml/pima-indians-diabetes-database
    // Remova o comentário de bloco abaixo para utilizar o exemplo 2.
    /*
    // Define a última coluna como a coluna de resultado
    RESULT_COLUMN = -1;

    // Carrega o dataset
    double **csv = read_csv("dataset-examples/diabetes.csv", &len_lines, &len_column);

    // Embaralha o dataset (opcional, recomendo NÃO USAR neste exemplo)
    //shuffle(dataset, len_lines, len_column);

    // Aloca as matrizes de treino e teste
    double **train_data = malloc(len_lines * sizeof(double*));
    for (int i = 0; i < len_lines; i++) {
        train_data[i] = malloc(len_column * sizeof(double));
    }
    double **test_data = malloc(len_lines * sizeof(double*));
    for (int i = 0; i < len_lines; i++) {
        test_data[i] = malloc(len_column * sizeof(double));
    }

    // Divide o dataset em treino e teste
    train_test(csv, len_lines, 80, train_data, test_data, &len_train, &len_test);

    // Separa ambos datasets de treino e teste em dados e resultados.
    double *train_result = copy_column(train_data, len_lines, len_column, RESULT_COLUMN);
    double *test_result = copy_column(test_data, len_lines, len_column, RESULT_COLUMN);

    remove_column(csv, &len_lines, &len_column,RESULT_COLUMN);
    free(csv);

    // Cria a rede neural (Perceptron)
    Perceptron *p;

    // Devido a um bug de ponteiros, é necessário fazer um backup do tamanho do dataset de teste e a quantidade de colunas (após o treino ele fica com valores aleatorios)
    int copy_len_column = len_column;
    int copy_len_test = len_test;

    // Treina a rede neural com o dataset de treino, utilizando o Perceptron
    fit(&p, 0.1, 1000, 16, train_data, train_result, len_column, len_train);

    // Testa a rede neural com o dataset de teste
    predict(&p, test_data, test_result, copy_len_column, copy_len_test);
    */
    dataframe csv = read_csv("dataset-examples/diabetes.csv", &len_lines, &len_column);

    head(csv, len_column, 7);

    printf("\n");
    system("pause");
    return 0;
}