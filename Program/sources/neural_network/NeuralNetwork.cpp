
#include "NeuralNetwork.h"

#include "neurons/InputNeuron.h"
#include "neurons/BiasNeuron.h"
#include "neurons/HiddenLayerNeuron.h"

using namespace neural_network;

NeuralNetwork::NeuralNetwork(std::vector<int> topology, functions::ActivationFunctions_E activationFunction) :
		neurons_(topology.size() + 2) {


	createInputNeurons();

	createHiddenLayers(topology, activationFunction);

	createOutputNeuron();

	createConnections();

}

NeuralNetwork::NeuralNetwork(NeuralNetwork::weights_t weights, functions::ActivationFunctions_E activationFunction) :
		neurons_(weights.size() + 1) {

	createInputNeurons();

	createHiddenLayers(weights, activationFunction);

	createOutputNeuron();

	createConnections(weights);
}

void NeuralNetwork::createInputNeurons() {

	neurons_.emplace_back();

	// 19 input neurons for each position in a house + 1 bias neuron
	for (int i = 0; i < 19; ++i) {
		neurons_.at(0).emplace_back(new neurons::InputNeuron());
	}
	neurons_.at(0).emplace_back(new neurons::BiasNeuron());

}

void NeuralNetwork::createOutputNeuron() {

	// output layer consists of only one output neuron
	outputNeuron_ = std::make_shared<neurons::OutputNeuron>();
	neurons_.at(neurons_.size() - 1).emplace_back(outputNeuron_);

}

void NeuralNetwork::createHiddenLayers(std::vector<int> topology, functions::ActivationFunctions_E activationFunction) {

	// hidden layers with number of neurons specified in the input argument + 1 bias neuron per layer

	auto hiddenLayers = topology.size();

	for (int i = 0; i < hiddenLayers; ++i) {
		for (int j = 0; j < topology.at(i); ++j) {
			neurons_.at(i + 1).emplace_back(new neurons::HiddenLayerNeuron(activationFunction));
		}
		neurons_.at(i + 1).emplace_back(new neurons::BiasNeuron());
	}

}

void NeuralNetwork::createHiddenLayers(NeuralNetwork::weights_t weights,
                                       functions::ActivationFunctions_E activationFunction) {


	auto netIterator = ++neurons_.begin();
	auto weightsIterator = ++weights.begin();

	for (; weightsIterator != weights.end();
	       ++netIterator, ++weightsIterator) {

		auto neuronsInLayer = weightsIterator->size() - 1;

		for (int i = 0; i < neuronsInLayer; ++i)
			netIterator->emplace_back(new neurons::HiddenLayerNeuron(activationFunction));

		netIterator->emplace_back(new neurons::BiasNeuron());
	}


}

void NeuralNetwork::createConnections() {

	for (auto i = neurons_.begin(), j = i + 1; j != neurons_.end(); ++i, ++j) {
		for (auto k = i->begin(); k != i->end(); ++k) {
			for (auto l = j->begin(); l != j->end(); ++l) {

				auto synapse = std::make_shared<neurons::Synapse>(*k, *l);

				(*k)->addOutputSynapse(synapse);
				(*l)->addInputSynapse(synapse);
			}
		}
	}
}

void NeuralNetwork::createConnections(NeuralNetwork::weights_t weights) {

	auto layerIt = weights.begin();

	for (auto i = neurons_.begin(), j = i + 1; j != neurons_.end(); ++i, ++j, layerIt++) {

		auto k = i->begin();
		auto weightK = layerIt->begin();

		for (; k != i->end(); ++k, ++weightK) {
			auto l = j->begin();
			auto weightsL = weightK->begin();
			for (; l != j->end(); ++l, ++weightsL) {

				auto synapse = std::make_shared<neurons::Synapse>(*k, *l, *weightsL);

				(*k)->addOutputSynapse(synapse);
				(*l)->addInputSynapse(synapse);
			}
		}
	}

}

std::vector<int> NeuralNetwork::getTopology() const {
	std::vector<int> topology(neurons_.size() - 2);

	auto outputLayer = --neurons_.end();
	for (auto iterator = ++neurons_.begin(); iterator != outputLayer; ++iterator)
		topology.emplace_back(iterator->size());

	return topology;
}

NeuralNetwork::weights_t NeuralNetwork::getWeights() const {

	weights_t weights(neurons_.size() - 1);

	auto firstDim = weights.begin();
	auto outputLayer = --neurons_.end();
	for (auto layer = neurons_.begin(); layer != outputLayer; ++layer, ++firstDim) {
		firstDim->emplace_back(layer->size());

		auto secondDim = firstDim->begin();
		for (auto neuron = layer->begin(); neuron != layer->end(); ++neuron, ++secondDim) {

			auto synapses = (*neuron)->getOutputSynapses();

			std::for_each(synapses.begin(), synapses.end(),
			              [&secondDim](auto synapse) {
				              secondDim->emplace_back(synapse->getWeight());
			              });

		}
	}

	return weights;
}

double NeuralNetwork::calculateHousesPrice(const house::NormalizedValuesHouse &house) {

	feedForward(house);
	return outputNeuron_->getValue();

}

void NeuralNetwork::feedForward(const house::NormalizedValuesHouse &house) {

	setInputs(house);

	for (auto i = neurons_.begin() + 1; i != neurons_.end(); ++i) {
		std::for_each(i->begin(), i->end(),
		              [](std::shared_ptr<neurons::Neuron> neuron) {
			              neuron->recalculateValue();
		              });
	}

}

void NeuralNetwork::setInputs(const house::NormalizedValuesHouse &house) {

	layer_t &inputLayer = neurons_.at(0);

	inputLayer.at(0)->setOutputValue(house.getDate());
	inputLayer.at(1)->setOutputValue(house.getBedrooms());
	inputLayer.at(2)->setOutputValue(house.getBathrooms());
	inputLayer.at(3)->setOutputValue(house.getSqftLiving());
	inputLayer.at(4)->setOutputValue(house.getSqftLot());
	inputLayer.at(5)->setOutputValue(house.getFloors());
	inputLayer.at(6)->setOutputValue(house.getWaterfront());
	inputLayer.at(7)->setOutputValue(house.getView());
	inputLayer.at(8)->setOutputValue(house.getCondition());
	inputLayer.at(9)->setOutputValue(house.getGrade());
	inputLayer.at(10)->setOutputValue(house.getSqftAbove());
	inputLayer.at(11)->setOutputValue(house.getSqftBasement());
	inputLayer.at(12)->setOutputValue(house.getYrBuilt());
	inputLayer.at(13)->setOutputValue(house.getYrRenovated());
	inputLayer.at(14)->setOutputValue(house.getZipcode());
	inputLayer.at(15)->setOutputValue(house.getLat());
	inputLayer.at(16)->setOutputValue(house.getLong());
	inputLayer.at(17)->setOutputValue(house.getSqftLiving15());
	inputLayer.at(18)->setOutputValue(house.getSqftLot15());

}






