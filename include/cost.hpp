#ifndef COST_HPP
#define COST_HPP
using namespace std;
#include "neurons.hpp"

double cost(neuron[], int, double *);

double ReLU(double);

double sigmoid(double);

double exp(double);

#endif // !COST_HPP