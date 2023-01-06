#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "toolkit.c"

// Perceptron's Structure, a supervised machine learning algorithm used for binary classification.
typedef struct {
    float alpha;
    float *relu_layer;
    double *weights;
}Perceptron;

// Trains the perceptron, performing the activation function and comparing the obtained result with the desired result, then adjusts the weights through the backpropagation function.
// Inputs: perceptron = structure of the perceptron, alpha = learning rate (value between 0 and 1), epochs = number of epochs, batch_size = len_column of the sample batch, dataset = matrix of the dataset, result = vector of desired results, len_column = number of columns, len_lines = number of len_lines.
void fit(Perceptron *perceptron, float alpha, int epochs, int batch_size, float **dataset, int *result, int len_column, int len_lines) {
    // TODO - BIAS IMPLEMENTATION
    int hits, steps = 0;

    time_t start_time = time(NULL);

    // Alocates the weights of the len_column of the number of neurons.
    int len_relu_layer = len_column - 1;
    perceptron->weights = malloc(len_relu_layer * sizeof(float));

    // Inicializes the weights with random values.
    for (int i = 0; i < len_relu_layer; i++) {
        perceptron->weights[i] = rand_int(-100, 100) / 100.0;
    }

    // Alocates the neurons with the len_column of the number of columns (1 ReLU neuron for each input)
    perceptron->relu_layer = malloc(len_relu_layer * sizeof(float));
    perceptron->alpha = alpha;

    // Starts the training.
    // For each epoch, it performs the activation function and adjusts the weights.
    for (int epoch = 0; epoch < epochs; epoch++) {
        // Alocates the error vector (result deviation).
        double batch_errors[batch_size];
        for (int i = 0; i < batch_size; i++) {

            // Generate a vector of "random" numbers, without repetition (theoretically).
            int rand_nums[batch_size];
            for (int j = 0; j < batch_size; j++) {
                rand_nums[j] = rand_int(0, len_lines - 1);
            }
            // Allocates the batch samples according to the generated "random" numbers.
            float sample_data[batch_size][len_relu_layer];
            int sample_result[batch_size];
            for (int j = 0; j < batch_size; j++) {
                for (int k = 0; k < len_relu_layer; k++) {
                    sample_data[j][k] = dataset[rand_nums[j]][k];
                }
                sample_result[j] = result[rand_nums[j]];
            }
            // For each ReLU neuron, performs the activation function and calculates the loss through the obtained result and the desired result, normalized by the sigmoidal neuron.
            float loss = 0;
            for (int j = 0; j < len_relu_layer; j++) {
                perceptron->relu_layer[j] = relu(sample_data[i][j]);
                loss = sample_result[i] - sigmoid(weighted_mean(perceptron->relu_layer, perceptron->weights, len_relu_layer));
                if (loss < 0) {
                    hits++;
                }
                steps++;
                // Adjusts the weights through the backpropagation function.
                backpropagation(perceptron->weights, loss, perceptron->relu_layer, len_relu_layer, perceptron->alpha);
            }
            // Stores the difference between the desired value and the obtained value in the vector, for each of the samples in the batch.
            batch_errors[i] = loss;
        }
        // Calculates the mean of the errors in the batch.
        float avarange_loss = weighted_mean(batch_errors, NULL, batch_size);

        // TODO - WARNING - remove this print for better performance during training, makes it about 20x faster.
        printf("\rEpoch: %d - loss: %.4f - average: %.4f", epoch, avarange_loss, (float)hits / (float)steps);
    }
    // Displays the results obtained with the training. Note, this is not yet an evaluation metric (done in the predict function), just an indication that the training is occurring.
    printf("\nFinal weights: \n");
    for (int i = 0; i < len_relu_layer; i++) {
        printf("[%i: %7.3f ]", i, (float)perceptron->weights[i]);
        printf("\n");
    }
    printf("\n\tTraining has finished. These are the results:");
    printf("\n\tExecution time: %d seconds", (int)(time(NULL) - start_time));
    printf("\n\tEpochs: %d - Batch_size: %d - Alpha: %f", epochs, batch_size, alpha);
    printf("\n\t\t ReLU neurons: %d + 1 Sigmoid neuron", len_relu_layer);
}

// Makes the prediction, using the test dataset and the trained perceptron weights, and returns the accuracy.
// Inputs: perceptron = structure of the perceptron, dataset = matrix of the dataset, result = vector of desired results, len_column = number of columns, len_lines = number of len_lines.
void predict(Perceptron *p, double **dataset, float *result, int len_column, int len_lines) {
    int hits, wrong = 0;

    // Performs the same activation functions and error calculation, but without adjusting the weights, instead just calculates the mean of errors and correct answers (accuracy).
    for (int i = 0; i < len_lines; i++) {
        float relu_neurons[len_column];
        for (int j = 0; j < len_column; j++) {
            relu_neurons[j] = relu(dataset[i][j]);
        }
        float error = result[i] - sigmoid(weighted_mean(p->relu_layer, p->weights, len_column));
        if (error < 0) {
            hits++;
        } else {
            wrong++;
        }
    }
    printf("\n\tPrediction with the test sample:");
    printf("\n\tCorrect: %d - Incorrect: %d - Accuracy: %.2f%%\n", hits, wrong, (float)hits / (float)(hits + wrong) * 100);
}