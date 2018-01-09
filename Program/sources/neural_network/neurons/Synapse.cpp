//
// Created by Piotr Żelazko on 06.01.2018.
//

#include "Synapse.h"
#include "RandomNumberGenerator.h"

using namespace neural_network::neurons;

const double Synapse::MAX_WEIGHT = 1.0;

Synapse::Synapse(const std::shared_ptr<Neuron> &begin, const std::shared_ptr<Neuron> &end) :
		begin_(begin),
		end_(end) {
	weight_ = RandomNumberGenerator<0,1>::generateDouble();
}

Synapse::Synapse(const std::shared_ptr<Neuron> &begin, const std::shared_ptr<Neuron> &end, double weight) :
		begin_(begin),
		end_(end),
		weight_(weight) {
}

double Synapse::getWeight() const {
	return weight_;
}

void Synapse::setWeight(double weight) {
	weight_ = weight;
}

double Synapse::getValue() const {
	return 0;
}
