//
// Created by Piotr Żelazko on 07.01.2018.
//

#ifndef PSZT_NEURAL_NETWORK_INPUTNEURON_H
#define PSZT_NEURAL_NETWORK_INPUTNEURON_H

#include "Neuron.h"

namespace neural_network {
	namespace neurons {
		class InputNeuron : public Neuron{
		public:
			InputNeuron();

			void setOutputValue(double value) override;
		};
	}
}


#endif //PSZT_NEURAL_NETWORK_INPUTNEURON_H
