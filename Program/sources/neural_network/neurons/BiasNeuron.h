//
// Created by Piotr Żelazko on 07.01.2018.
//

#ifndef PSZT_NEURAL_NETWORK_BIASNEURON_H
#define PSZT_NEURAL_NETWORK_BIASNEURON_H

#include "InputNeuron.h"

namespace neural_network {
	namespace neurons {
		class BiasNeuron : public Neuron {
		public:
			BiasNeuron() { value_ = 1.0; }

			~BiasNeuron() override = default;

			void addOutputSynapse(const std::shared_ptr<Synapse> &outputSynapse) override;

			void addInputSynapse(const std::shared_ptr<Synapse> &inputSynapse) override;

			void recalculateValue() override;

			void computeError() override;

		};
	}
}

#endif //PSZT_NEURAL_NETWORK_BIASNEURON_H
