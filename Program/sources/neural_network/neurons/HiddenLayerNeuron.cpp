//
// Created by Piotr Żelazko on 08.01.2018.
//

#include "HiddenLayerNeuron.h"


using namespace neural_network::neurons;

HiddenLayerNeuron::HiddenLayerNeuron(neural_network::functions::ActivationFunctions_E functions) :
		functions_(functions::ActivationFunctionsBank::getFunctionAndDerivative(functions)) {

}

void HiddenLayerNeuron::addInputSynapse(
		const std::shared_ptr<neural_network::neurons::Synapse> &inputSynapse) {

	inputSynapses_.emplace_back(inputSynapse);

}

void HiddenLayerNeuron::addOutputSynapse(
		const std::shared_ptr<neural_network::neurons::Synapse> &outputSynapse) {

	outputSynapses_.emplace_back(outputSynapse);

}

void HiddenLayerNeuron::recalculateValue() {

	delta_ = 0.0;
	inputSum_ = 0.0;

	for(auto& synapse : inputSynapses_)
		inputSum_ += synapse->recalculateValue();

	value_ = functions_.first(inputSum_);

}

void HiddenLayerNeuron::computeError() {

	delta_ = 0.0;

	for(auto& synapse : outputSynapses_)
		delta_ += synapse->getBackPropagationValue();

	delta_ = functions_.second(delta_);

}
