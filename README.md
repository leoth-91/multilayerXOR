
# Multilayer Perceptron

A couple of years ago I had to come up with a project for a course and decided to code a **Neural Network in C++**.

This repository is a slightly brushed up version of this project, it makes use of the original Neural Network class written for the course (header/NeuralNetwork.h) and I have added python scripts for conveniently generating data and plotting errors.

[Neural Network](#Neural Network) | [Pipeline](#Pipeline) | [Exclusive OR](#Exclusive OR) | [Usage](#Usage)

## Neural Network



![equ](https://latex.codecogs.com/gif.latex?log(y)=\beta_0&space;&plus;&space;\beta_1&space;x&space;&plus;&space;u)

<!-- https://latex.codecogs.com/gif.latex?%5Cmathrm%7BRAE%7D%20%5Clongrightarrow%20%5Cfrac%7B%5Cxi%5Ccdot%20%5Cmathrm%7BRAE%7D%20&plus;%20%5Cmathrm%7Bloss%7D%7D%7B1&plus;%5Cxi%7D%20%5Capprox%20%5Cmathrm%7BRAE%7D%20&plus;%20%5Cmathrm%7Bloss%7D/%5Cxi -->

<!-- \mathrm{RAE} \longrightarrow \frac{\xi\cdot \mathrm{RAE} + \mathrm{loss}}{1+\xi} \approx \mathrm{RAE} + \mathrm{loss}/\xi -->

the intution here is: the smoothing factor xi adjusts how much a single loss value contributes tu the Recent Average Error


<!-- https://latex.codecogs.com/gif.latex?%5Cmathrm%7BRAE%7D%20%5Clongrightarrow%20%5Cfrac%7B%5Cxi%5Ccdot%20%5Cmathrm%7BRAE%7D%20&plus;%20%5Cmathrm%7Bloss%7D%7D%7B1&plus;%5Cxi%7D -->

<!-- https://latex.codecogs.com/gif.latex?%5Cmathrm%7BRAE%7D%20%5Clongrightarrow%20%5Cmathrm%7BRAE%7D%20&plus;%20%5Cmathrm%7Bloss%7D/%5Cxi%5Cquad%20%28%5Cmathrm%7Bapproximately%7D%29 -->


## Pipeline

# Generating data
# Training


## Exclusive OR

Many binary operators (eg. AND, OR) can be modeled by a simple Neural Network. 

The Exclusive OR (XOR) is a particular binary operation, as it is not linearly separable and therefore requires a **hidden layer**.

The XOR function should return a true value if the two inputs are not equal and a false value if they are equal:

 Input 1 | Input 2 | Output
 ---------------------------
    0    |    0    |    0
    0    |    1    |    1
    1    |    0    |    1
    1    |    1    |    0
---------------------------


```python
# pseudocode
a = 1
b = 2
print(a+b)
```


## Usage

# Producing data
The data generating script utilizes **numpy**:

```bash
pip install numpy
```
then run
```bash
python data_gen.py --N_train=100 --N_test=100
```
other options
-- path: the path, default is 'data/'
-- ext: extension of output files, default is '.dat'

The trainging:
```bash
g++ -o perceptron.o perceptron.cpp
./perceptron
```

