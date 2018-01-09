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

			double getWeight() const;

			void setWeight(double weight);

			double getValue() const;
			double updateValue();

			void updateWeight(double eta, int batchSize);
			void resetTemporaryData();

			virtual ~Synapse() = default;

		private:
			std::weak_ptr<Neuron> begin_;
			std::weak_ptr<Neuron> end_;

			double weight_;
			double value_;

			double nablaWeight_;
			double deltaNablaWeight_;

			static const double MAX_WEIGHT;
		};
	}
}

#endif //PSZT_NEURAL_NETWORK_SYNAPSE_H
