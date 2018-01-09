//
// Created by Piotr Żelazko on 05.01.2018.
//

#include "Neuron.h"

using namespace neural_network::neurons;

void Neuron::addInputSynapse(const std::shared_ptr<Synapse> &inputSynapse) {
	throw std::runtime_error("This method should not be used in this type");
}

void Neuron::addOutputSynapse(const std::shared_ptr<Synapse> &outputSynapse) {
	throw std::runtime_error("This method should not be used in this type");
}

void Neuron::setOutputValue(double value) {
	throw std::runtime_error("This method should not be used in this type");
}


