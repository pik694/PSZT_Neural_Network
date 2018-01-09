//
// Created by Piotr Żelazko on 07.01.2018.
//

#ifndef PSZT_NEURAL_NETWORK_OUTPUTNEURON_H
#define PSZT_NEURAL_NETWORK_OUTPUTNEURON_H

#include "Neuron.h"

namespace neural_network {
	namespace neurons {
		class OutputNeuron : public Neuron{
		public:
			OutputNeuron() = default;

			void addInputSynapse(const std::shared_ptr<Synapse> &inputSynapse) override;

			virtual ~OutputNeuron() = default;
		};
	}
}

#endif //PSZT_NEURAL_NETWORK_OUTPUTNEURON_H
