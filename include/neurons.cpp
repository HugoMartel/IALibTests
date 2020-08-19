#include "neurons.hpp"
#include "cost.hpp"
#include <iostream>
#include <cstdlib>
using namespace std;

#define SIGMOID_TO_USE 1 //ReLU
//#define SIGMOID_TO_USE 2 //Sigmoid

// --------- NEURONS ---------
neuron::neuron(int previousNeurons = 1, double b = 0)
{
    weight = new double[previousNeurons];
    bias = b;
    value = 0;
    if (debug)
        cout << "--Neuron created--\n";
}

// neuron::neuron(const neuron &v)
// {
// }

neuron::~neuron()
{
    delete[] weight;
    if (debug)
        cout << "--Neuron deleted--\n";
}

void neuron::changeWeight(double d, int index)
{
    weight[index] = d;
}

void neuron::show()
{
    cout << "Weight: " << weight << ", Bias: " << bias << ", Value: " << value << '\n';
}

// --------- LAYERS ---------

/*
    i corresponds to the layer's posision
    nAmount corresponds to the number of neurons in the layer
    */
layer::layer(int nAmount = 1)
{
    neuronAmount = nAmount;

    neurons = new neuron[nAmount];

    if (debug)
        cout << "--Layer created--\n";
}

// layer::layer(const layer &)
// {
// }

layer::~layer()
{
    delete[] neurons;
    if (debug)
        cout << "--Layer deleted--\n---------------------------\n";
}

// --------- NETWORKS ---------

/*
    i corresponds to the number of layers in the network
    ar is an array containing the number of neurons per layer (i = len(ar))
    */
network::network(const int i, const int *ar)
{
    layerAmount = i;

    neuronAmountPerLayer = new int[i];
    for (int k = 0; k < i; k++)
        neuronAmountPerLayer[k] = ar[k];

    layers = new layer[i];
    for (int k = 0; k < i; k++)
    {
        layers[k].neuronAmount = ar[k];
        delete[] layers[k].neurons;            //Delete array previously created with the default layer's constructor
        layers[k].neurons = new neuron[ar[k]]; //Create the new array with the correct size
        //Replaces the default NULL pointers assigned to the neuron weights
        if (k)
        {
            //for each j neuron of the k layer assign a weight for each previous layer's neuron
            for (int j = 0; j < layers[k].neuronAmount; j++)
            {
                delete[] layers[k].neurons[j].weight;
                layers[k].neurons[j].weight = new double[layers[k - 1].neuronAmount];
                for (int l = 0; l < layers[k - 1].neuronAmount; l++)
                    layers[k].neurons[j].weight[l] = 0;
            }
        }
    }

    if (debug)
        cout << "--Network successfully created--\n";
}

// network::network(const network &)
// {
// }

network::~network()
{
    delete[] layers;
    delete[] neuronAmountPerLayer;
    if (debug)
        cout << "--Network successfully deleted--\n";
}

//Prints out the network's layout
void network::show()
{
    cout << "Network : " << layers << '\n';
    //Shows each layer
    for (int k = 0; k < layerAmount; k++)
    {
        cout << "Layer " << k << " :  ";
        //Shows the amount of neurons
        for (int j = 0; j < neuronAmountPerLayer[k]; j++)
            cout << "o ";
        //Total amount of neurons
        cout << "- " << layers[k].neuronAmount << '\n'
             << layers[k].neurons << ": ";
        //Labelize the neurons
        for (int j = 0; j < layers[k].neuronAmount; j++)
            cout << j << ',';
        cout << '\n';
    }
}

//Initialises the network with random values
//Randomises each bias between -2 and 2
//Randomises each weight between -1 and 1
void network::init()
{
    srand(time(NULL));

    for (int i = 0; i < layerAmount; i++)
    {
        //Skip the first neurons layer used for inputs
        for (int j = 1; j < layers[i].neuronAmount; j++)
        {
            layers[i].neurons[j].bias = ((-2) + ((double)rand() / RAND_MAX) * 4);
            //Init each neuron's weights
            if (i)
            {
                for (int l = 0; l < layers[i - 1].neuronAmount; l++)
                    layers[i].neurons[j].weight[l] = ((-1) + ((double)rand() / RAND_MAX) * 2);
            }
        }
    }
}

// σ(Wa + b)
void network::calc(int functionToUse = SIGMOID_TO_USE)
{
    int tmp;
    //for each layer after the first one
    for (int l = 1; l < layerAmount; l++)
    {
        //for each neuron of the l layer
        for (int n = 0; n < neuronAmountPerLayer[l]; n++)
        {
            tmp = 0; //Stores the new value of a neuron
            //for each previous neuron (Wa)
            for (int p = 0; p < neuronAmountPerLayer[l - 1]; p++)
            {
                tmp += layers[l].neurons[n].weight[p] * layers[l - 1].neurons[p].value;
            }
            // Add the bias (Wa + b)
            tmp += layers[l].neurons[n].bias;
            //Squish the value between 0 and 1 σ(Wa + b)
            switch (functionToUse)
            {
            case 1:
                //ReLU
                tmp = ReLU(tmp);
                break;
            case 2:
                //Sigmoid
                tmp = sigmoid(tmp);
                break;

            default:
                break;
            }
            //Now do it again for each neuron of the layer
        }
        //Now do it again for each layer of the network
    }
    if (debug)
        cout << "--Neurons values successfully updated--";
}

void network::input(const double * inputs) {
    //Copy the values into the first layer's neurons' values
    for (int n = 0; n < neuronAmountPerLayer[0]; n++)
        layers[0].neurons[n].value = inputs[n];
    if (debug)
        cout << "--Inputs successfully inserted--";
}