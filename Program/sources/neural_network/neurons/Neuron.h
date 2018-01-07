//
// Created by Piotr Żelazko on 05.01.2018.
//

#ifndef PSZT_NEURAL_NETWORK_NEURON_H
#define PSZT_NEURAL_NETWORK_NEURON_H


#include <vector>
#include <functional>

namespace neural_network{
	namespace neurons {
		class Neuron;
	}
}

#include "Synapse.h"

namespace neural_network {
	namespace  neurons {
		class Neuron {

		public:

			explicit Neuron(std::function<double(double)> function, std::function<double(double)> derivative);

			double calculateOutputValue();

			void updateInputValue();

			void updateOutputValue();

			double getOutputValue() const;

			void addInputSynapse(const std::shared_ptr<Synapse> &inputSynapse);

			void addOutputSynapse(const std::shared_ptr<Synapse> &outputSynapse);

			virtual ~Neuron() = default;

		private:

			std::function<double(double)> function_;
			std::function<double(double)> derivative_;
			double inputValue_;
			double outputValue_;
			std::vector<std::shared_ptr<Synapse> > inputSynapses_;
			std::vector<std::shared_ptr<Synapse> > outputSynapses_;

			double sumInputs();

		};
	}

};


#endif //PSZT_NEURAL_NETWORK_NEURON_H
