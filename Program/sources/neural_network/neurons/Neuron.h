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
			Neuron() = default;

			double getValue() const { return value_; }

			virtual double recalculateValue() { return getValue(); }

			virtual void addInputSynapse(const std::shared_ptr<Synapse> &inputSynapse);

			virtual void addOutputSynapse(const std::shared_ptr<Synapse> &outputSynapse);

			virtual void setOutputValue(double value);

			const std::vector<std::shared_ptr<Synapse> >& getOutputSynapses(){return outputSynapses_;}

			virtual void updateOutputSynapses(double eta, int batchSize);

			virtual ~Neuron() = default;

		protected:

			std::vector<std::shared_ptr<Synapse> > inputSynapses_;
			std::vector<std::shared_ptr<Synapse> > outputSynapses_;

			double value_;
			double inputSum_;


		};
	}
}


#endif //PSZT_NEURAL_NETWORK_NEURON_H
