//
// Created by Piotr Żelazko on 05.01.2018.
//

#include "Neuron.h"


neural_network::Neuron::Neuron(std::function<double(double)> function, std::function<double(double)> derivative) :
        function_(function),
        derivative_(derivative)
{

}

double neural_network::Neuron::getOutputValue() const {
    return output_value_;
}

double neural_network::Neuron::sumInputs() {
    double sum = 0;
    for (const std::shared_ptr<Synapse> &s : input_synapses_) {
        sum += s->getValue();
    }
    return sum;
}

double neural_network::Neuron::calculateOutputValue() {
    updateInputValue();
    updateOutputValue();
    return output_value_;
}

void neural_network::Neuron::addInputSynapse(const std::shared_ptr<neural_network::Synapse> &inputSynapse) {
    input_synapses_.push_back(inputSynapse);
}

void neural_network::Neuron::addOutputSynapse(const std::shared_ptr<neural_network::Synapse> &outputSynapse) {
    output_synapses_.push_back(outputSynapse);
}

void neural_network::Neuron::updateOutputValue() {
    output_value_ = function_(input_value_);
}

void neural_network::Neuron::updateInputValue() {
    input_value_ = sumInputs();

}


