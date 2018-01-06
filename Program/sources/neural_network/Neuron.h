//
// Created by Piotr Żelazko on 05.01.2018.
//

#ifndef PSZT_NEURAL_NETWORK_NEURON_H
#define PSZT_NEURAL_NETWORK_NEURON_H


#include <vector>
#include <functional>
#include "Synapse.h"

namespace neural_network {
    class Neuron {

    public:

        explicit Neuron(std::function<double(double)> function, std::function<double(double)> derivative);

        double getOutputValue() const;
        void setOutputValue(double outputValue);
        void addInputSynapse(Synapse inputSynapse);
        void addOutputSynapse(Synapse outputSynapse);

    private:

        std::function<double(double)> function_;
        std::function<double(double)> derivative_;
        double outputValue;
        std::vector<Synapse> input_synapses_;
        std::vector<Synapse> output_synapses_;

        double sumInputs();
        double calculateOutputValue();

    };

};


#endif //PSZT_NEURAL_NETWORK_NEURON_H
