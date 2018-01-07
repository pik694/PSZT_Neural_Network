//
// Created by Piotr Żelazko on 07.01.2018.
//

#include "BiasNeuron.h"

neural_network::neurons::BiasNeuron::BiasNeuron():
Neuron([](double val){return val;}, [](double val){return 1;})
{
	//TODO
}
