//
// Created by Piotr Żelazko on 07.01.2018.
//

#include "OutputNeuron.h"

using namespace neural_network::neurons;

OutputNeuron::OutputNeuron(neural_network::functions::ActivationFunctions_E functions):
		functions_(functions::ActivationFunctionsBank::getFunctionAndDerivative(functions)) {

}

void OutputNeuron::addInputSynapse(const std::shared_ptr<Synapse> &inputSynapse) {
	inputSynapses_.emplace_back(inputSynapse);
}

void OutputNeuron::calculateOutputError(const house::NormalizedValuesHouse &house,
                                        std::function<double(double, double)> costFunctionDerivative) {

	delta_ = costFunctionDerivative(value_, house.getPrice())*functions_.second(inputSum_);

}
