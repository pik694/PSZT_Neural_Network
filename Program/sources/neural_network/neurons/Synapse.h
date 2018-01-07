//
// Created by Piotr Żelazko on 06.01.2018.
//

#ifndef PSZT_NEURAL_NETWORK_SYNAPSE_H
#define PSZT_NEURAL_NETWORK_SYNAPSE_H

#include <memory>

namespace neural_network{
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

			double getWeight() const;

			void setWeight(double weight);

			double getValue() const;

			virtual ~Synapse() = default;

		private:
			std::weak_ptr<Neuron> begin_;
			std::weak_ptr<Neuron> end_;
			double weight_;

			static const double MAX_WEIGHT;
		};
	}
}

#endif //PSZT_NEURAL_NETWORK_SYNAPSE_H