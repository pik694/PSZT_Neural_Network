//
// Created by Piotr Żelazko on 07.01.2018.
//

#ifndef PSZT_NEURAL_NETWORK_BIASNEURON_H
#define PSZT_NEURAL_NETWORK_BIASNEURON_H

#include "InputNeuron.h"

namespace neural_network {
	namespace neurons {
		class BiasNeuron : public InputNeuron {
		public:
			BiasNeuron() { value_ = 1.0; }

			void addInputSynapse(const std::shared_ptr<Synapse>&) override {}

			void recalculateValue() override {}

			~BiasNeuron() override = default;

		};
	}
}

#endif //PSZT_NEURAL_NETWORK_BIASNEURON_H
