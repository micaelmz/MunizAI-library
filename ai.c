#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

#define EULER 2.71828

// Função para calcular a média ponderada de uma lista de números
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

//int rand_int(int min, int max) {
//    unsigned long long x;
//    asm volatile("rdtsc" : "=A" (x));
//    const unsigned long long a = 1103515245;
//    const unsigned long long c = 12345;
//    const unsigned long long m = 1ull << 31;
//    x = (a * x + c) % m;
//    return min + (int)(x / (m / (max - min + 1)));
//}

int rand_int(int min, int max) {
    srand(clock());
    LARGE_INTEGER performance_counter;
    QueryPerformanceCounter(&performance_counter);
    srand((unsigned int)performance_counter.QuadPart);
    return rand() % (max - min + 1) + min;
}


// Função para calcular potência
float pow(float x, int y) {
    float result = 1;
    for (int i = 0; i < y; i++) {
        result = result * x;
    }
    return result;
}

// Função para calcular a função ReLU
float relu(float x) {
    if (x < 0) {
        return 0;
    }
    return x;
}

// Função para calcular a função sigmóide
// sigmoid(x) = 1 / (1 + exp(-x))
float sigmoid(float x) {
    return 1 / (1 + pow(EULER, -x));
}

// Estrutura do Perceptron
typedef struct {
    float alpha;
    float *relu_neurons;
    double *weights;
}Perceptron;


// Função para dividir o dataset em treino e teste, basicamente divide o dataset em duas partes, cortando as linhas
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


// Função para realizar a retropropagação do erro
// Δw = α × erro × entrada
void backpropagation(float *weights, float error, float *relu_neurons, int size, float alpha) {
    for (int i = 0; i < size; i++) {
        weights[i] = weights[i] + alpha * error * relu_neurons[i];
    }
}

// Função para realizar a predição
void predict(Perceptron *p, double **dataset, int size, float *result, int rows) {
    int hits = 0;
    int wrong = 0;
    for (int i = 0; i < rows; i++) {
        float relu_neurons[size];
        for (int j = 0; j < size; j++) {
            relu_neurons[j] = relu(dataset[i][j]);
        }
        float error = result[i] - sigmoid(weighted_mean(p->relu_neurons, p->weights, size));
        if (error < 0) {
            hits++;
        } else {
            wrong++;
        }
    }
    printf("\n\tAcertos: %d - Erros: %d - Acuracia: %.2f%%\n", hits, wrong, (float)hits / (float)(hits + wrong) * 100);
}


// Método fit do Perceptron
void fit(Perceptron *perceptron, float alpha, int epochs, int *result, int batch_size, float **dataset, int size, int rows) {
    int hits = 0;
    int steps = 0;

    time_t start_time = time(NULL);

    int relu_neurons_units = size-1; // Altere esta linha para obter o número correto de camadas ReLU
    perceptron->weights = malloc(relu_neurons_units * sizeof(float));
    // put random weights in the perceptron
    for (int i = 0; i < relu_neurons_units; i++) {
        perceptron->weights[i] = rand_int(-100, 100) / 100.0;
    }

    perceptron->relu_neurons = malloc(relu_neurons_units * sizeof(float));
    perceptron->alpha = alpha;

    for (int epoch = 0; epoch < epochs; epoch++) {
        double batch_errors[batch_size];
        for (int i = 0; i < batch_size; i++) {

            // pega as amostras
            int rand_nums[batch_size];
            for (int j = 0; j < batch_size; j++) {
                rand_nums[j] = rand_int(0, rows - 1);
            }
            float sample_data[batch_size][relu_neurons_units];
            int sample_result[batch_size];
            for (int j = 0; j < batch_size; j++) {
                for (int k = 0; k < relu_neurons_units; k++) {
                    sample_data[j][k] = dataset[rand_nums[j]][k];
                }
                sample_result[j] = result[rand_nums[j]];
            }
            float error = 0;
            for (int j = 0; j < relu_neurons_units; j++) {
                perceptron->relu_neurons[j] = relu(sample_data[i][j]);
                error = sample_result[i] - sigmoid(weighted_mean(perceptron->relu_neurons, perceptron->weights, relu_neurons_units));
                if (error < 0) {
                    hits++;
                }
                steps++;
                backpropagation(perceptron->weights, error, perceptron->relu_neurons, relu_neurons_units, perceptron->alpha);
            }
            batch_errors[i] = error;
        }
        float mean_error = weighted_mean(batch_errors, NULL, batch_size);
        printf("Epoch: %d - erro: %.4f - media: %.2f%%", epoch, mean_error, (float)hits / (float)steps * 100);
        printf("\n");
    }
    //printf("Acuracia: %.2f%%\n", (float)hits / (float)steps * 100);
    printf("Pesos finais: ");
    for (int i = 0; i < relu_neurons_units; i++) {
        printf("[%i: %.4f ]", i, perceptron->weights[i]);
        printf("\n");
    }
    printf("\n\n\n\tO treinamento terminou. Esses sao os resultados:");
    printf("\n\tTempo de execucao: %d segundos", (int)(time(NULL) - start_time));
}