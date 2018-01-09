//
// Created by Piotr Żelazko on 07.01.2018.
//

#include "OutputNeuron.h"

using namespace neural_network::neurons;

void OutputNeuron::addInputSynapse(const std::shared_ptr<Synapse> &inputSynapse) {
	inputSynapses_.emplace_back(inputSynapse);
}
