//
// Created by Piotr Żelazko on 05.01.2018.
//

#include "Neuron.h"

using namespace neural_network::neurons;

Neuron::Neuron(std::function<double(double)> function, std::function<double(double)> derivative) :
		function_(function),
		derivative_(derivative) {

}

double Neuron::getOutputValue() const {
	return outputValue_;
}



double Neuron::recalculateOutputValue() {
	updateInputValue();
	updateOutputValue();
	return outputValue_;
}

void Neuron::addInputSynapse(const std::shared_ptr<Synapse> &inputSynapse) {
	inputSynapses_.emplace_back(inputSynapse);
}

void Neuron::addOutputSynapse(const std::shared_ptr<Synapse> &outputSynapse) {
	outputSynapses_.emplace_back(outputSynapse);
}

void Neuron::updateOutputValue() {
	outputValue_ = function_(inputValue_);
}

void Neuron::updateInputValue() {

	inputValue_ = sumInputs();

}

double Neuron::sumInputs() {
	double sum = 0;
	for (const std::shared_ptr<Synapse> &s : inputSynapses_) {
		sum += s->getValue();
	}
	return sum;
}


