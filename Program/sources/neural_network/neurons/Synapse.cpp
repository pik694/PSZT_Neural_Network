//
// Created by Piotr Żelazko on 06.01.2018.
//

#include "Synapse.h"
#include "RandomNumberGenerator.h"

using namespace neural_network::neurons;

const double Synapse::MAX_WEIGHT = 1.0;

Synapse::Synapse(const std::shared_ptr<Neuron> &begin, const std::shared_ptr<Neuron> &end) :
		begin_(begin),
		end_(end),
		value_(0.0),
		delta_(0.0)
{
	weight_ = RandomNumberGenerator<0,1>::generateDouble();
}

Synapse::Synapse(const std::shared_ptr<Neuron> &begin, const std::shared_ptr<Neuron> &end, double weight) :
		begin_(begin),
		end_(end),
		weight_(weight),
		value_(0.0),
		delta_(0.0)
{}

double Synapse::getWeight() {
	return weight_;
}

double Synapse::getValue() {
	return value_;
}

double Synapse::recalculateValue() {

	return value_ = weight_ * begin_.lock()->getValue();
}

double Synapse::getBackPropagationValue() {

	delta_ += begin_.lock()->getValue() * end_.lock()->getDelta();

	return weight_ * end_.lock()->getDelta();
}

void Synapse::updateWeight(double factor) {

	weight_ -= factor * delta_;
	delta_ = 0.0;
}




