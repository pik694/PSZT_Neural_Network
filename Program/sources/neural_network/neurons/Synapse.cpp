//
// Created by Piotr Żelazko on 06.01.2018.
//

#include "Synapse.h"
#include "RandomNumberGenerator.h"

using namespace neural_network::neurons;

const double Synapse::MAX_WEIGHT = 1.0;

double Synapse::getWeight() const {
	return weight_;
}

void Synapse::setWeight(double weight_) {
	Synapse::weight_ = weight_;
}

Synapse::Synapse(const std::shared_ptr<Neuron>& begin, const std::shared_ptr<Neuron>& end):
		begin_ (begin),
		end_ (end)
{
	weight_ = RandomNumberGenerator::getInstance()->generateNumber(0.0, MAX_WEIGHT);
}

double Synapse::getValue() const {
	return 0;
}
