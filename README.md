
# Multilayer Perceptron

A couple of years ago I had to come up with a project for a course and decided to code a **Neural Network in C++**.

This repository is a slightly brushed up version of this project, it makes use of the original Neural Network class written for the course (header/NeuralNetwork.h) and I have added python scripts for conveniently generating data and plotting errors.

[Neural Network](#NeuralNetwork) | [Pipeline](#Pipeline) | [Exclusive OR](#ExclusiveOR) | [Usage](#Usage)

## Neural Network

The Neural Network has 3 layers, input, output and a hidden layer. The numbers of Neurons per layer is variable, here of course we have

 - 2 input Neuons

 - 2 hidden Neuons

 - 1 output Neuons

Activation: tanh()

Loss: RMS



At every step a smoothed error measurement: is put out

![equ](https://latex.codecogs.com/gif.latex?%5Cmathrm%7BRAE%7D%20%5Clongrightarrow%20%5Cfrac%7B%5Cxi%5Ccdot%20%5Cmathrm%7BRAE%7D%20&plus;%20%5Cmathrm%7Bloss%7D%7D%7B1&plus;%5Cxi%7D)

the intution here is: the smoothing factor xi adjusts how much a single loss value contributes tu the Recent Average Error

![equ](https://latex.codecogs.com/gif.latex?%5Cmathrm%7BRAE%7D%20%5Clongrightarrow%20%5Cmathrm%7BRAE%7D%20&plus;%20%5Cmathrm%7Bloss%7D/%5Cxi%5Cquad%20%28%5Cmathrm%7Bapproximately%7D%29)





## Pipeline

# Generating data
# Training


## Exclusive OR

Many binary operators (eg. AND, OR) can be modeled by a simple Neural Network. 

The Exclusive OR (XOR) is a particular binary operation, as it is not linearly separable and therefore requires a **hidden layer**.

The XOR function should return a true value if the two inputs are not equal and a false value if they are equal:

![equ](https://latex.codecogs.com/gif.latex?%5Cbegin%7Btabular%7D%7Bc%7Cc%7Cc%7D%5Chline%20Input%201%20%26Input%202%20%26Output%20%5C%5C%20%5Chline%5Chline%200%20%260%20%260%20%5C%5C%20%5Chline%200%20%261%20%261%20%5C%5C%20%5Chline%201%20%260%20%261%20%5C%5C%20%5Chline%201%20%261%20%260%20%5C%5C%20%5Chline%20%5Cend%7Btabular%7D)



## Usage

# Producing data




then run
```bash
g++ -o data_gen data_gen.cpp
./data_gen
```
<!-- other options
-- path: the path, default is 'data/'
-- ext: extension of output files, default is '.dat'
 -->
The trainging:
```bash
g++ -o training training.cpp
./training
```

The plotting script utilizes **numpy** and **matplotlib**:

```bash
pip install numpy
pip install matplotlib
```
then run
```bash
python plot.py 
```









