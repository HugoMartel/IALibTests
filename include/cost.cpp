#include <iostream>
#include "neurons.hpp"
using namespace std;

//Rectified Linear Unit
double ReLU(double x)
{
    if (x > 0)
        return x;
    else
        return 0;
}

//Approximated exp with taylor's formula to the 6th degree
double exp(double x)
{
    return (1 + x + (x * x) / 2 + (x * x * x) / 6 + (x * x * x * x) / 24 + (x * x * x * x * x) / 120 + (x * x * x * x * x * x) / 720);
}

//To squish a value between 0 and 1
double sigmoid(double x)
{
    return (1 / (1 + exp(-x)));
}

//Cost function of a neural network's layer
double cost(neuron output[], int n, double *optimalOutput)
{
    double tmp = 0;
    for (int i = 0; i < n; i++)
        tmp += (output[i].value - optimalOutput[i]) * (output[i].value - optimalOutput[i]);
    return tmp;
}