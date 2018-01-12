//
// Created by Piotr Żelazko on 07.01.2018.
//


#include "BiasNeuron.h"

using namespace neural_network::neurons;


void BiasNeuron::addOutputSynapse(const std::shared_ptr<Synapse> &outputSynapse) {
	outputSynapses_.emplace_back(outputSynapse);
}

void BiasNeuron::addInputSynapse(const std::shared_ptr<Synapse> &) {}

void BiasNeuron::recalculateValue() {}

void BiasNeuron::computeError() {

	for(auto& synapse : outputSynapses_)
		synapse->getBackPropagationValue();

}

