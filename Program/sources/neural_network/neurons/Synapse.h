//
// Created by Piotr Żelazko on 06.01.2018.
//

#ifndef PSZT_NEURAL_NETWORK_SYNAPSE_H
#define PSZT_NEURAL_NETWORK_SYNAPSE_H

#include <memory>

namespace neural_network {
	namespace neurons {
		class Synapse;
	}
}

#include "neural_network/neurons/Neuron.h"

namespace neural_network {
	namespace neurons {

		class Synapse {
		public:

			Synapse(const std::shared_ptr<Neuron> &begin, const std::shared_ptr<Neuron> &end);
			Synapse(const std::shared_ptr<Neuron> &begin, const std::shared_ptr<Neuron> &end, double weight);

			double getWeight();
			double getValue();

			double recalculateValue();
			double getBackPropagationValue();
			void updateWeight(double eta, int batchSize);

			virtual ~Synapse() = default;

		private:
			std::weak_ptr<Neuron> begin_;
			std::weak_ptr<Neuron> end_;

			double weight_;
			double value_;
			double delta_;

			static const double MAX_WEIGHT;
		};
	}
}

#endif //PSZT_NEURAL_NETWORK_SYNAPSE_H
