//
// Created by Piotr Żelazko on 07.01.2018.
//

#ifndef PSZT_NEURAL_NETWORK_OUTPUTNEURON_H
#define PSZT_NEURAL_NETWORK_OUTPUTNEURON_H

#include <house/NormalizedValuesHouse.h>
#include <neural_network/ActivationFunctionsBank.h>
#include "Neuron.h"

namespace neural_network {
	namespace neurons {
		class OutputNeuron : public Neuron {
		public:
			OutputNeuron(functions::ActivationFunctions_E functions);

			void addInputSynapse(const std::shared_ptr<Synapse> &inputSynapse) override;


			void recalculateValue() override;

			void calculateOutputError(const house::NormalizedValuesHouse &house,
			                          std::function<double(double, double)> costFunctionDerivative);

			virtual ~OutputNeuron() = default;

		private:

			const std::pair<std::function<double(double)>, std::function<double(double)>> functions_;

		};
	}
}

#endif //PSZT_NEURAL_NETWORK_OUTPUTNEURON_H
