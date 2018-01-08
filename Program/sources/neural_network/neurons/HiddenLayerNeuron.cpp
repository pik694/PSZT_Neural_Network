//
// Created by Piotr Żelazko on 08.01.2018.
//

#include "HiddenLayerNeuron.h"


using namespace neural_network::neurons;
double HiddenLayerNeuron::recalculateValue() {

	double sum = 0.0;
	for(auto& synapse : inputSynapses_){
		sum += synapse->getValue();
	}

	return 	value_ = functions_.first(sum);
}

void HiddenLayerNeuron::addInputSynapse(
		const std::shared_ptr<neural_network::neurons::Synapse> &inputSynapse) {

	inputSynapses_.emplace_back(inputSynapse);

}

void HiddenLayerNeuron::addOutputSynapse(
		const std::shared_ptr<neural_network::neurons::Synapse> &outputSynapse) {

	outputSynapses_.emplace_back(outputSynapse);

}
