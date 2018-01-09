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
		nablaWeight_(0.0),
		deltaNablaWeight_(0.0),
		value_(0.0)
{
	weight_ = RandomNumberGenerator<0,1>::generateDouble();
}

Synapse::Synapse(const std::shared_ptr<Neuron> &begin, const std::shared_ptr<Neuron> &end, double weight) :
		begin_(begin),
		end_(end),
		weight_(weight),
		nablaWeight_(0.0),
		deltaNablaWeight_(0.0),
		value_(0.0)
{}

double Synapse::getWeight() const {
	return weight_;
}

void Synapse::setWeight(double weight) {
	weight_ = weight;
}

double Synapse::getValue() const {
	return value_;
}

double Synapse::updateValue() {
	deltaNablaWeight_ = 0.0;
	return value_ = begin_.lock()->getValue() * weight_;
}

void Synapse::updateWeight(double eta, int batchSize) {
	weight_ -= (eta/batchSize) * nablaWeight_;
}

void Synapse::resetTemporaryData() {
	nablaWeight_ = 0.0;
}

