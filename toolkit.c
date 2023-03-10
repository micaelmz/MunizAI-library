#include <stdlib.h>
#include <windows.h>
#include <time.h>

#define EULER 2.71828
#define matrix double**

// Calculates the power of a number (base ^ exponent).
// Inputs: x = base, y = exponent.
float pow(float x, int y) {
    float result = 1;
    for (int i = 0; i < y; i++) {
        result = result * x;
    }
    return result;
}

// Generates a random integer within a specified range.
// Inputs: min = minimum number, max = maximum number.
int rand_int(int min, int max) {
    srand(clock());
    LARGE_INTEGER performance_counter;
    QueryPerformanceCounter(&performance_counter);
    srand((unsigned int)performance_counter.QuadPart);
    return rand() % (max - min + 1) + min;
}

// Calculates the weighted mean of a vector. If weights are not provided, it calculates the arithmetic mean.
// Inputs: values = vector of values, weights = vector of weights, size = size of the vectors.
float weighted_mean(float *values, float *weights, int size) {
    float sum = 0;
    float w_sum = 0;
    for (int i = 0; i < size; i++) {
        if (weights == NULL){
            sum = sum + values[i];
            w_sum = w_sum + 1;
        } else {
            sum = sum + values[i] * weights[i];
            w_sum = w_sum + weights[i];
        }
    }
    return sum / w_sum;
}

// Calculates the Rectified Linear Unit activation function for a given value. If the value is less than 0, it returns 0, otherwise it returns the value.
// Input: x = function x.
float relu(float x) {
    if (x < 0) {
        return 0;
    }
    return x;
}

// Calculates the sigmoidal activation function, which is a mathematical logistic function that returns a value between 0 and 1. Defined by sigmoid(x) = 1 / (1 + exp(-x))
// Input: x = function x.
float sigmoid(float x) {
    return 1 / (1 + pow(EULER, -x));
}

// Divides a dataset into training and test sets.
// Inputs: dataset = matrix of the dataset, len_lines = number of lines, proportion = proportion of training, train = matrix of training, test = matrix of test, len_test = number of lines of the test.
void train_test(matrix dataset, int len_lines, int proportion, matrix train, matrix test, int *len_train, int *len_test) {
    *len_train = len_lines * proportion / 100;
    *len_test = len_lines - *len_train;

    for (int i = 0; i < *len_train; i++) {
        train[i] = dataset[i];
    }
    for (int i = 0; i < *len_test; i++) {
        test[i] = dataset[*len_train + i];
    }
}

// Ajusts the weights using the backpropagation algorithm. Defined by ??w = ??lpha ?? loss ?? input, where alpha is the learning rate and loss is the difference between the expected output and the actual output.
// Inputs: weights = vector of weights, loss = difference between the desired value and the obtained value, relu_layer = vector of neurons filled with inputs, len_relu_layer = len_relu_layer, alpha = learning rate.
void backpropagation(float *weights, float loss, float *relu_layer, int len_relu_layer, float alpha) {
    for (int i = 0; i < len_relu_layer; i++) {
        weights[i] = weights[i] + alpha * loss * relu_layer[i];
    }
}


// TODO - OVERFITTING ALGORITHMS - NOT YET IMPLEMENTED

// TODO - OPTIMIZATION ALGORITHMS SUCH AS GRADIENT DESCENT AND ADAM - NOT YET IMPLEMENTED

// TODO - RANDOM USING SYSTEM NOISE - NOT YET IMPLEMENTED