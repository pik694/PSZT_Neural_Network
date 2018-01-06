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
    return outputValue;
}

void neural_network::Neuron::setOutputValue(double outputValue) {
    Neuron::outputValue = outputValue;
}

void neural_network::Neuron::addInputSynapse(neural_network::Synapse inputSynapse) {
    input_synapses_.push_back(inputSynapse);
}

void neural_network::Neuron::addOutputSynapse(neural_network::Synapse outputSynapse) {
    output_synapses_.push_back(outputSynapse);

}


double neural_network::Neuron::sumInputs() {
    double sum = 0;
    for (Synapse s : input_synapses_) {
        sum += s.getValue();
    }
    return sum;
}

double neural_network::Neuron::calculateOutputValue() {
    return function_(sumInputs());
}


