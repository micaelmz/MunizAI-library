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
Making it in C instead of Python helps me to understand how things work behind the scenes. I hope you can learn something here with me 😉.

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
len_lines: 768, len_column: 9
len_lines: 768, len_column: 8
Epoch: 999 - result deviation: -0.8750 - average: 0.8171
Final weights:
[0: 642079364251079370447859426311152519692572361916656279210498235414430060875984315686578569038790656.0000 ]
[1: 77083697666112455876630953934879190545269180558078475637623342763127658152134431692687322255684796416.0000 ]
[2: 32178026611381223930825425980962017217847208223517684462505621691783168453339244560654189588289421312.0000 ]
[3: 0.2200 ]
[4: 0.2500 ]
[5: 0.2800 ]
[6: 0.3200 ]

        Training has finished. These are the results:
        Execution time: 3 seconds
        Epochs: 1000 - Batch size: 16 - Alpha: 0.100000
                ReLU neurons: 7 + 1 Sigmoid neuron
        Prediction with the test sample:
        Correct: 130 - Incorrect: 24 - Accuracy: 84.42%
```
<i>You can find this example in main.c</i>

### ToolKit.c
The ToolKit module contains a set of utility functions that are commonly used in the development of neural networks. These functions include activation functions such as the sigmoid function $\sigma(x) = \frac{1}{1 + e^{-x}}$; mathematical constants; the backpropagation function $\Delta w = \alpha \times (expected - obtained) \times input$; random number generator algorithms, and other features that are useful in the development of AI modules.

### Pandas.c
Pandas is a module that contains some useful functions for data manipulation and visualization. It is based on the Python Pandas library, but with some evident differences.<br>

### NLP.c
#### in development
