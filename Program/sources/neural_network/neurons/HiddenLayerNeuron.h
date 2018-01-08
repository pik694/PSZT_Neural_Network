//
// Created by Piotr Żelazko on 08.01.2018.
//

#ifndef PSZT_NEURAL_NETWORK_HIDDENLAYERNEURON_H
#define PSZT_NEURAL_NETWORK_HIDDENLAYERNEURON_H

#include "Neuron.h"
#include "neural_network/ActivationFunctionsBank.h"

namespace neural_network {
	namespace neurons {
		class HiddenLayerNeuron : public Neuron {
		public:
			HiddenLayerNeuron(functions::ActivationFunctions_E);

			double recalculateValue() override;

			void addInputSynapse(const std::shared_ptr<Synapse> &inputSynapse) override;

			void addOutputSynapse(const std::shared_ptr<Synapse> &outputSynapse) override;

			virtual ~HiddenLayerNeuron() = default;

		private:
			const std::pair<std::function<double(double)>, std::function<double(double)>> functions_;
		};
	}
}


#endif //PSZT_NEURAL_NETWORK_HIDDENLAYERNEURON_H
