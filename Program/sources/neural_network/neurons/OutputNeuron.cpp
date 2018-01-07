//
// Created by Piotr Żelazko on 07.01.2018.
//

#include "OutputNeuron.h"

using namespace neural_network::neurons;

OutputNeuron::OutputNeuron():
	Neuron([](double a){return a;}, [](double){return 1;}) {}