using namespace std;
#include <iostream>
#include "../include/neurons.hpp"
#include "../include/cost.hpp"

bool debug = false;

#define LAYERS_AMOUNT 5
#define INPUT_NEURONS_AMOUNT 15
#define OUTPUT_NEURONS_AMOUNT 10

int main(int argc, char *argv[])
{
    //debug option check
    string debugTest = "--debug";
    for (int i = 0; i < argc; i++)
    {
        if (!debugTest.compare(argv[i]))
            debug = true;
    }

    int tab[LAYERS_AMOUNT] = {INPUT_NEURONS_AMOUNT, 8, 5, 5, OUTPUT_NEURONS_AMOUNT};
    network test(LAYERS_AMOUNT, tab);

    cout << "\n-------------------------\n";

    test.show();

    cout << "\n-------------------------\n";

    test.layers[0].neurons[0].show();
    test.layers[1].neurons[7].show();
    cout << sizeof(test.layers[1].neurons[7].weight) << '\n';
    test.init();
    cout << "--Network Randomised--\n";
    test.layers[0].neurons[0].show();
    test.layers[1].neurons[7].show();
    cout << sizeof(test.layers[1].neurons[7].weight) << '\n';

    cout << "\n-------------------------\n";

    double testOutput[OUTPUT_NEURONS_AMOUNT] = {0, 0, 0, 0, 1, 0, 0, 0, 0, 0};
    cout << "Cost : " << cost(test.layers[0].neurons, test.neuronAmountPerLayer[test.layerAmount - 1], testOutput) << '\n';

    cout << "*** --end-- ***\n";

    return 0;
}