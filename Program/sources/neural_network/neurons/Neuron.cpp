//
// Created by Piotr Żelazko on 05.01.2018.
//

#include "Neuron.h"

using namespace neural_network::neurons;

void Neuron::addInputSynapse(const std::shared_ptr<Synapse>&) {
	throw std::runtime_error("This method should not be used in this type");
}

void Neuron::addOutputSynapse(const std::shared_ptr<Synapse> &) {
	throw std::runtime_error("This method should not be used in this type");
}

void Neuron::setOutputValue(double) {
	throw std::runtime_error("This method should not be used in this type");
}

void Neuron::recalculateValue() {
	throw std::runtime_error("This method should not be used in this type");
}

void Neuron::computeError() {
	throw std::runtime_error("This method should not be used in this type");
}

void Neuron::updateOutputWeights(double factor) {

	for(auto synapse : outputSynapses_)
		synapse->updateWeight(factor);
}


Neuron::~Neuron() {}


