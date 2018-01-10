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

			virtual void addInputSynapse(const std::shared_ptr<Synapse> &inputSynapse);
			virtual void addOutputSynapse(const std::shared_ptr<Synapse> &outputSynapse);

			virtual void setOutputValue(double value);

			virtual void recalculateValue();
			virtual void computeError();

			const std::vector<std::shared_ptr<Synapse>>& getOutputSynapses(){return outputSynapses_;}

			double getValue(){return value_;}
			double getDelta(){return delta_;}

			void updateOutputWeights(double factor);

			virtual ~Neuron() = 0;

		protected:

			double value_ = 0.0;
			double inputSum_ = 0.0;

			double delta_;

			std::vector<std::shared_ptr<Synapse> > inputSynapses_;
			std::vector<std::shared_ptr<Synapse> > outputSynapses_;

		};
	}
}


#endif //PSZT_NEURAL_NETWORK_NEURON_H
