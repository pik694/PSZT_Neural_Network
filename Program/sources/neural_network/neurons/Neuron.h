//
// Created by Piotr Żelazko on 05.01.2018.
//

#ifndef PSZT_NEURAL_NETWORK_NEURON_H
#define PSZT_NEURAL_NETWORK_NEURON_H


#include <vector>
#include <functional>

namespace neural_network {
	namespace neurons {
		class Neuron;
	}
}

#include "Synapse.h"

namespace neural_network {
	namespace neurons {
		class Neuron {

		public:

			explicit Neuron(std::function<double(double)> function, std::function<double(double)> derivative);

			double recalculateOutputValue();

			double getOutputValue() const;

			void addInputSynapse(const std::shared_ptr<Synapse> &inputSynapse);

			void addOutputSynapse(const std::shared_ptr<Synapse> &outputSynapse);

			virtual void
			setOutputValue(double value) {
				throw std::domain_error("In this type of neuron you cannot set output value");
			}

			virtual ~Neuron() = default;

		private:

			double sumInputs();

			void updateInputValue();

			void updateOutputValue();

			std::function<double(double)> function_;
			std::function<double(double)> derivative_;

			std::vector<std::shared_ptr<Synapse> > inputSynapses_;
			std::vector<std::shared_ptr<Synapse> > outputSynapses_;

			double inputValue_;
			double outputValue_;


		};
	}

};


#endif //PSZT_NEURAL_NETWORK_NEURON_H
