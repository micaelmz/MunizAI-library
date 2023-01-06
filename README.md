# Getting started with the Muniz AI library.

![banner](https://raw.githubusercontent.com/micaelmz/micaelmz/main/images/muniz-ai/muniz-ai-banner.png)


Muniz AI is a library created for personal study purposes. I am a computer engineering junior sophister, with a strong interest in data science and artificial intelligence.
I created this library to help me improve my undesting in AI fields, such as<br>

- Deep & Machine Learning
- Natural Languague Processing
- Computer Vision
- Decision Tree Algorithms
- Reforced Learning


This means that I am building this project while learning about it.
<br>
Making it in C instead of Python helps me to understand how things work behind the scenes. I hope you can learn something here with me. 😉

## Modules
### Perceptron.c
Perceptron is a simple machine learning algorithm that was one of the first models of machine learning to be developed.<br> 
It was created as a way to simulate the functioning of the human brain in a basic neural network.<br>
Perceptron is a binary classification model, which means it is used to predict whether an example belongs to one of two possible classes (e.g., spam or not spam, yes or no, success or failure).<br> 
It is trained using labeled examples and makes predictions based on a set of adjustable weights.<br>

#### Example
```c
Perceptron *p;
fit(&p, 0.1, 1000, 16, train_data, train_result, len_column, len_train);
predict(&p, test_data, test_result, copy_len_column, copy_len_test);
```
Output in cmd:
```cmd
0      6  148   72   35    0  33.60  0.63   50    1
1      1   85   66   29    0  26.60  0.35   31    0
2      8  183   64    0    0  23.30  0.67   32    1
3      1   89   66   23   94  28.10  0.17   21    0
4      0  137   40   35  168  43.10  2.29   33    1
...  ...  ...  ...  ...  ...    ...   ...  ...
763   10  101   76   48  180  32.90  0.17   63    0
764    2  122   70   27    0  36.80  0.34   27    0
765    5  121   72   23  112  26.20  0.24   30    0
766    1  126   60    0    0  30.10  0.35   47    1
767    1   93   70   31    0  30.40  0.32   23    0

[768 rows x 9 columns]
Epoch: 999 - result deviation: 2.5933 - average: 0.80927
Final weights:
[0:     inf ]
[1:     inf ]
[2:     inf ]
[3:   0.800 ]
[4:   0.800 ]
[5:   0.830 ]
[6:   0.860 ]

        Training has finished. These are the results:
        Execution time: 11 seconds
        Epochs: 1000 - Batch_size: 16 - Alpha: 0.100000
                 ReLU neurons: 7 + 1 Sigmoid neuron
        Prediction with the test sample:
        Correct: 130 - Incorrect: 24 - Accuracy: 84.42%
```
<i>You can find this example in `main.c`</i>

### ToolKit.c
The ToolKit module contains a set of utility functions that are commonly used in the development of neural networks. These functions include activation functions such as the sigmoid function $\sigma(x) = \frac{1}{1 + e^{-x}}$; mathematical constants; the backpropagation function $\Delta w = \alpha \times (expected - obtained) \times input$; random number generator algorithms, and other features that are useful in the development of AI modules.

### Pandas.c
Pandas is a module that contains some useful functions for data manipulation and visualization. It is based on the Python Pandas library, but with some evident differences.<br>

### NLP.c
> in development
