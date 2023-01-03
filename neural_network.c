#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>

#define EULER 2.71828

// Estrutura do Perceptron, um algoritmo de aprendizado de máquina supervisionado, utilizado para classificação binária.
typedef struct {
    float alpha;
    float *relu_neurons;
    double *weights;
}Perceptron;

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

// Treina o perceptron, realizando a função de ativação, e comparando o resultado obtido com o desejado, então ajusta os pesos através da função de retropropagação.
// Entradas: perceptron = estrutura do perceptron, alpha = taxa de aprendizado (valor entre 0 e 1), epochs = quantidade de épocas, batch_size = tamanho do lote de amostras, dataset = matriz do dataset, result = vetor dos resultados desejados, size = quantidade de colunas, rows = quantidade de linhas.
void fit(Perceptron *perceptron, float alpha, int epochs, int batch_size, float **dataset, int *result, int size, int rows) {
    // TODO - IMPLEMENTAR O BIAS
    int hits, steps = 0;

    time_t start_time = time(NULL);

    // Aloca os pesos do tamanho da quantidade de neuronios.
    int relu_neurons_units = size-1;
    perceptron->weights = malloc(relu_neurons_units * sizeof(float));

    // Inicializa os pesos com valores aleatórios.
    for (int i = 0; i < relu_neurons_units; i++) {
        perceptron->weights[i] = rand_int(-100, 100) / 100.0;
    }

    // Aloca os neurônios com o tamanho da quantidade de colunas (1 ReLU neuron para cada input)
    perceptron->relu_neurons = malloc(relu_neurons_units * sizeof(float));
    perceptron->alpha = alpha;

    // Realiza o treinamento.
    for (int epoch = 0; epoch < epochs; epoch++) {
        // Aloca o vetor dos erros.
        double batch_errors[batch_size];
        for (int i = 0; i < batch_size; i++) {

            // Gera um vetor de números "aleatórios", sem repetição (teoricamente).
            int rand_nums[batch_size];
            for (int j = 0; j < batch_size; j++) {
                rand_nums[j] = rand_int(0, rows - 1);
            }
            // Aloca as amostras do lote, de acordo com os números "aleatórios" gerados.
            float sample_data[batch_size][relu_neurons_units];
            int sample_result[batch_size];
            for (int j = 0; j < batch_size; j++) {
                for (int k = 0; k < relu_neurons_units; k++) {
                    sample_data[j][k] = dataset[rand_nums[j]][k];
                }
                sample_result[j] = result[rand_nums[j]];
            }
            // Para cada neuronio ReLU, realiza a função de ativação e calcula o erro através do resultado obtido e o desejado, normalizado pelo neurônio sigmoidal.
            float error = 0;
            for (int j = 0; j < relu_neurons_units; j++) {
                perceptron->relu_neurons[j] = relu(sample_data[i][j]);
                error = sample_result[i] - sigmoid(weighted_mean(perceptron->relu_neurons, perceptron->weights, relu_neurons_units));
                if (error < 0) {
                    hits++;
                }
                steps++;
                // Ajusta os pesos, através da função de retropropagação.
                backpropagation(perceptron->weights, error, perceptron->relu_neurons, relu_neurons_units, perceptron->alpha);
            }
            // Armazena a diferença entre o desejado e o obtido no vetor, para cada uma das amostras do lote.
            batch_errors[i] = error;
        }
        // Calcula a média dos erros do lote.
        float mean_error = weighted_mean(batch_errors, NULL, batch_size);

        // TODO - AVISO - remova esse print para obter uma melhor performance no treinamento, torna cerca de 20x mais rápido.
        printf("\rEpoch: %d - distancia do resultado: %.4f - media: %.4f", epoch, mean_error, (float)hits / (float)steps);
    }
    // Exibe os resultados obtidos com o treinamento. Detalhe, isso não é ainda uma métrica de avaliação (feito na função predict), apenas um indicativo de que o treinamento está ocorrendo.
    printf("\nPesos finais: \n");
    for (int i = 0; i < relu_neurons_units; i++) {
        printf("[%i: %.4f ]", i, perceptron->weights[i]);
        printf("\n");
    }
    printf("\n\n\n\tO treinamento terminou. Esses sao os resultados:");
    printf("\n\tTempo de execucao: %d segundos", (int)(time(NULL) - start_time));
    printf("\n\tEpochs: %d - Batch_size: %d - Alpha: %f", epochs, batch_size, alpha);
    printf("\n\t\t Neuronios ReLU: %d + 1 Neuronio Sigmoid", relu_neurons_units);
}

// Realiza a predição, através do dataset de testes, utilizando os pesos do perceptron treinado, e retorna a acurácia.
// Entradas: perceptron = estrutura do perceptron, dataset = matriz do dataset, result = vetor dos resultados desejados, size = quantidade de colunas, rows = quantidade de linhas.
void predict(Perceptron *p, double **dataset, float *result, int size, int rows) {
    int hits, wrong = 0;

    // Realiza as mesmas funções de ativação e cálculo de erro, porém, sem ajustar os pesos, invés disso, apenas calcula a media de erros e acertos (acurácia).
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
    printf("\n\tPredicao com a amostra de testes:");
    printf("\n\tAcertos: %d - Erros: %d - Acuracia: %.2f%%\n", hits, wrong, (float)hits / (float)(hits + wrong) * 100);
}

// TODO - ALGORITMOS DE OVERLIFITING - AINDA NÃO IMPLEMENTADOS

// TODO - ALGORTIMOS DE OTIMIZAÇÃO COMO GRADIENTE DESCENDENTE E ADAM - AINDA NÃO IMPLEMENTADOS

// TODO - RANDOM UTILIZANDO RUIDOS DO SISTEMA - AINDA NÃO IMPLEMENTADOS