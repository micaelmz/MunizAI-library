#include <stdlib.h>
#include <windows.h>
#include <time.h>

#define EULER 2.71828

// Calcula potência de um número (base ^ expoente).
// Entradas: x = base, y = expoente.
float pow(float x, int y) {
    float result = 1;
    for (int i = 0; i < y; i++) {
        result = result * x;
    }
    return result;
}

// Gera um número inteiro aleatório entre um intervalo. Detalhe: esse gerador é péssimo, mas é o que da pra fazer em C!
// Entradas: min = número mínimo, max = número máximo.
int rand_int(int min, int max) {
    srand(clock());
    LARGE_INTEGER performance_counter;
    QueryPerformanceCounter(&performance_counter);
    srand((unsigned int)performance_counter.QuadPart);
    return rand() % (max - min + 1) + min;
}

// Calcula a média ponderada de um vetor, caso nào seja passado os pesos (W = NULL), se torna uma função de média aritimetica.
// Entradas: n = vetor dos valores, w = vetor dos pesos, size = tamanho.
float weighted_mean(float *n, float *w, int size) {
    float sum = 0;
    float w_sum = 0;
    for (int i = 0; i < size; i++) {
        if (w == NULL){
            sum = sum + n[i];
            w_sum = w_sum + 1;
        } else {
            sum = sum + n[i] * w[i];
            w_sum = w_sum + w[i];
        }
    }
    return sum / w_sum;
}

// Calcular a função de ativação ReLU (Rectified Linear Unit) de um vetor. Se o valor for menor que 0, retorna 0, caso contrário, retorna o valor.
// Entrada: x = x da função.
float relu(float x) {
    if (x < 0) {
        return 0;
    }
    return x;
}

// Calcula a função de ativação sigmoidal, que é uma função logística matemática, que retorna um valor entre 0 e 1. Definida por sigmoid(x) = 1 / (1 + exp(-x))
// Entrada: x = x da função.
float sigmoid(float x) {
    return 1 / (1 + pow(EULER, -x));
}

// Divide o dataset entre treino e teste.
// Entradas; dataset = matriz do dataset, len_lines = quantidade de linhas, proportion = proporção de treino, train = matriz de treino, test = matriz de teste, len_test = quantidade de linhas do teste.
void train_test(double **dataset, int len_lines, int proportion, double **train, double **test, int *len_train, int *len_test) {
    *len_train = len_lines * proportion / 100;
    *len_test = len_lines - *len_train;

    for (int i = 0; i < *len_train; i++) {
        train[i] = dataset[i];
    }
    for (int i = 0; i < *len_test; i++) {
        test[i] = dataset[*len_train + i];
    }
}

// Ajusta os pesos através de um algortimo de retropropagação. Definido por Δw = αlpha × erro × entrada, onde o erro é definido por erro = (desejado - obtido).
// Entradas: weights = vetor dos pesos, error = diferença entre o desejado e o obtido, relu_neurons = vetor dos neurônios preenchidos com as entradas, size = tamanho, alpha = taxa de aprendizado.
void backpropagation(float *weights, float error, float *relu_neurons, int size, float alpha) {
    for (int i = 0; i < size; i++) {
        weights[i] = weights[i] + alpha * error * relu_neurons[i];
    }
}

// TODO - ALGORITMOS DE OVERLIFITING - AINDA NÃO IMPLEMENTADOS

// TODO - ALGORTIMOS DE OTIMIZAÇÃO COMO GRADIENTE DESCENDENTE E ADAM - AINDA NÃO IMPLEMENTADOS

// TODO - RANDOM UTILIZANDO RUIDOS DO SISTEMA - AINDA NÃO IMPLEMENTADOS