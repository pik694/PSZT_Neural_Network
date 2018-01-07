#include "neurons/BiasNeuron.h"
#include "neurons/InputNeuron.h"
#include "neurons/OutputNeuron.h"
#include "NeuralNetwork.h"


using namespace neural_network;

NeuralNetwork::NeuralNetwork(std::vector<int> neuronsInLayer, std::function<double(double)> function,
                             std::function<double(double)> derivative) :
		neurons_(neuronsInLayer.size() + 2) {


	// 20 input neurons for each position in house + 1 bias neuron
	for (int i = 0; i < 20; ++i) {
		neurons_.at(0).emplace_back(new neurons::InputNeuron());
	}
	neurons_.at(0).emplace_back(new neurons::BiasNeuron());

	// hidden layers with number of neurons specified in the input argument + 1 bias neuron per layer

	auto hiddenLayers = neuronsInLayer.size();

	for (int i = 1; i <= hiddenLayers; ++i) {
		for (int j = 0; j < neuronsInLayer.at(i); ++j) {
			neurons_.at(i).emplace_back(new neurons::Neuron(function, derivative));
		}
		neurons_.at(i).emplace_back(new neurons::BiasNeuron());
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

};

