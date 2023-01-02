#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
    float *weights;
}Perceptron;


// Função para dividir o dataset em treino e teste
void train_test(){
    // TODO
}


// Função para realizar a retropropagação do erro
// Δw = α × erro × entrada
void backpropagation(float *weights, float error, float *relu_neurons, int size, float alpha) {
    for (int i = 0; i < size; i++) {
        weights[i] = weights[i] + alpha * error * relu_neurons[i];
    }
}

// Método fit do Perceptron
void fit(Perceptron *perceptron, float alpha, int epochs, int *result, int bach_size, float **dataset, int size) {
    int hits = 0;
    int steps = 0;

    time_t start_time = time(NULL);

    int relu_neurons_units = size; // Altere esta linha para obter o número correto de camadas ReLU
    perceptron->weights = malloc(relu_neurons_units * sizeof(float));
    perceptron->relu_neurons = malloc(relu_neurons_units * sizeof(float));
    perceptron->alpha = alpha;

    for (int epoch = 0; epoch < epochs; epoch++) {
        for (int i = 0; i < bach_size; i++) {
            int rand_nums[bach_size];
            float sample_data[bach_size][relu_neurons_units];
            int sample_result[bach_size];
            // Gere números aleatórios aqui para selecionar a amostra de dados e resposta
            for (int j = 0; j < bach_size; j++) {
                for (int k = 0; k < relu_neurons_units; k++) {
                    sample_data[j][k] = dataset[rand_nums[j]][k];
                }
                sample_result[j] = result[rand_nums[j]];
            }
            for (int j = 0; j < relu_neurons_units; j++) {
                perceptron->relu_neurons[j] = relu(sample_data[i][j]);
                float error = sample_result[i] - sigmoid(weighted_mean(perceptron->relu_neurons, perceptron->weights, relu_neurons_units));
                if (error < 0) {
                    hits++;
                }
                steps++;
                backpropagation(perceptron->weights, error, perceptron->relu_neurons, relu_neurons_units, perceptron->alpha);
            }
        }

        float batch_errors[bach_size];
        // Preencha o vetor batch_errors aqui
        float media_erro = weighted_mean(batch_errors, NULL, bach_size);
        printf("Epoch: %d - erro: %.4f - media: %.4f - pesos: ", epoch, error, hits / steps);
        for (int i = 0; i < relu_neurons_units; i++) {
            printf("%.4f ", perceptron->weights[i]);
        }
        printf("\n");
    }
}