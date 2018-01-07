#include "neurons/BiasNeuron.h"
#include "neurons/InputNeuron.h"
#include "neurons/OutputNeuron.h"
#include "NeuralNetwork.h"


using namespace neural_network;

NeuralNetwork::NeuralNetwork(std::vector<int> neuronsInLayer, std::function<double(double)> function,
                             std::function<double(double)> derivative) :
		neurons_(neuronsInLayer.size() + 2) {


	// 19 input neurons for each position in house + 1 bias neuron
	for (int i = 0; i < 19; ++i) {
		neurons_.at(0).emplace_back(new neurons::InputNeuron());
	}
	neurons_.at(0).emplace_back(new neurons::BiasNeuron());

	// hidden layers with number of neurons specified in the input argument + 1 bias neuron per layer

	auto hiddenLayers = neuronsInLayer.size();

	for (int i = 0; i < hiddenLayers; ++i) {
		for (int j = 0; j < neuronsInLayer.at(i); ++j) {
			neurons_.at(i+1).emplace_back(new neurons::Neuron(function, derivative));
		}
		neurons_.at(i+1).emplace_back(new neurons::BiasNeuron());
	}

	// output layer consists of only one output neuron

	neurons_.at(neurons_.size() - 1).emplace_back(new neurons::OutputNeuron());

	// create synapses between neurons

	for (auto i = neurons_.begin(), j = i + 1 ; j != neurons_.end(); ++i, ++j) {
		for (auto k = i->begin(); k != i->end(); ++k){
			for(auto l = j->begin(); l != j->end(); ++l){

				std::shared_ptr<neurons::Synapse> synapse = std::make_shared<neurons::Synapse>(*k,*l);

				(*k)->addOutputSynapse(synapse);
				(*l)->addInputSynapse(synapse);
			}
		}
	}

}

double NeuralNetwork::feedForward(const house::NormalizedValuesHouse& house) {

	setInputs(house);

	for (auto i = neurons_.begin() + 1; i != neurons_.end(); ++i){
		std::for_each(i->begin(), i->end(),
		              [](std::shared_ptr<neurons::Neuron> neuron){
			neuron->calculateOutputValue();
		});
	}

	return getNetResult();

}

void NeuralNetwork::setInputs(const NormalizedValuesHouse& house) {

	layer_t& inputLayer = neurons_.at(0);

	//TODO: waits until proper method is created
	// inputLayer.at(0)->setOutputValue(house.getDate());
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

};

double NeuralNetwork::getNetResult() {

	auto outputNeuronLayer = --neurons_.end();

	return outputNeuronLayer->at(0)->getOutputValue();

}



