//
// Created by Piotr Żelazko on 07.01.2018.
//

#include "InputNeuron.h"

using namespace neural_network::neurons;

InputNeuron::InputNeuron():Neuron([](double a){return a;}, [](double a){return 1;})
{

}
