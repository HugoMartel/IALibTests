#ifndef NEURONS_H
#define NEURONS_H

extern bool debug;

/*
weight
bias
*/
class neuron
{
public:
    double *weight;
    double bias;
    double value; //Between 0 and 1
    neuron(int, double);
    //neuron(const neuron &);
    ~neuron();
    void changeWeight(double, int);
    void show();
};

/*
neuronAmount > number of neurons contained by the layer
neurons      > array listing the layer's neurons
*/
class layer
{
public:
    int neuronAmount;
    neuron *neurons;

    layer(int);
    //layer(const layer &);
    ~layer();
};

/*
layerAmount          > number of layers (:= len(neuronAmountPerLayer))
neuronAmountPerLayer > array containing the number of neurons per layer (by index)
layers               > array listing the layers
*/
class network
{
public:
    int layerAmount;
    int *neuronAmountPerLayer;
    layer *layers;

    network(const int, const int *);
    //network(const network &);
    ~network();
    void show();
    void init();
};

#endif // !NEURONS_H