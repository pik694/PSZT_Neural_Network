//
// Created by Piotr Żelazko on 07.01.2018.
//

#include "InputNeuron.h"

using namespace neural_network::neurons;

void InputNeuron::addOutputSynapse(const std::shared_ptr<Synapse> &outputSynapse) {

	outputSynapses_.emplace_back(outputSynapse);

}

void InputNeuron::setOutputValue(double value) {
	value_ = value;
}


void InputNeuron::computeError() {
	for(auto& synapse : outputSynapses_)
		delta_ += synapse->getBackPropagationValue();
}
