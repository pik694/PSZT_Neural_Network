//
// Created by Piotr Żelazko on 05.01.2018.
//

#ifndef PSZT_NEURAL_NETWORK_NEURON_H
#define PSZT_NEURAL_NETWORK_NEURON_H


#include <vector>
#include <functional>

namespace neural_network{
    class Neuron;
}

#include "Synapse.h"

namespace neural_network {
    class Neuron {

    public:

        explicit Neuron(std::function<double(double)> function, std::function<double(double)> derivative);

        double calculateOutputValue();
        void updateInputValue();
        void updateOutputValue();
        double getOutputValue() const;
        void addInputSynapse(const std::shared_ptr<Synapse> &inputSynapse);
        void addOutputSynapse(const std::shared_ptr<Synapse>  &outputSynapse);

    private:

        std::function<double(double)> function_;
        std::function<double(double)> derivative_;
        double input_value_;
        double output_value_;
        std::vector<std::shared_ptr<Synapse> > input_synapses_;
        std::vector<std::shared_ptr<Synapse> > output_synapses_;

        double sumInputs();

    };

};


#endif //PSZT_NEURAL_NETWORK_NEURON_H
