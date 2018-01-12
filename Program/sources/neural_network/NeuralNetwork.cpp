#include <boost/range/adaptor/reversed.hpp>
#include <random>


#include "NeuralNetwork.h"
#include "neurons/InputNeuron.h"
#include "neurons/BiasNeuron.h"
#include "neurons/HiddenLayerNeuron.h"
#include "progress/ProgressStatusManager.h"

using namespace neural_network;

template<typename T>
NeuralNetwork<T>::NeuralNetwork(std::vector<int> topology, functions::ActivationFunctions_E activationFunction) :
		neurons_(topology.size() + 2) {

	createInputNeurons();

	createHiddenLayers(topology, activationFunction);

	createOutputNeuron(activationFunction);

	createConnections();

}

template<typename T>
NeuralNetwork<T>::NeuralNetwork(NeuralNetwork<T>::weights_t weights, functions::ActivationFunctions_E activationFunction) :
		neurons_(weights.size() + 1) {

	createInputNeurons();

	createHiddenLayers(weights, activationFunction);

	createOutputNeuron(activationFunction);

	createConnections(weights);
}

template<typename T>
void NeuralNetwork<T>::createOutputNeuron(functions::ActivationFunctions_E functions) {

	// output layer consists of only one output neuron
	outputNeuron_ = std::make_shared<neurons::OutputNeuron>(functions);
	neurons_.at(neurons_.size() - 1).emplace_back(outputNeuron_);

}

template<typename T>
void NeuralNetwork<T>::createHiddenLayers(std::vector<int> topology, functions::ActivationFunctions_E activationFunction) {

	// hidden layers with number of neurons specified in the input argument + 1 bias neuron per layer

	auto hiddenLayers = topology.size();

	for (unsigned int i = 0; i < hiddenLayers; ++i) {
		for (int j = 0; j < topology.at(i); ++j) {
			neurons_.at(i + 1).emplace_back(new neurons::HiddenLayerNeuron(activationFunction));
		}
		neurons_.at(i + 1).emplace_back(new neurons::BiasNeuron());
	}

}

template<typename T>
void NeuralNetwork<T>::createHiddenLayers(NeuralNetwork::weights_t weights,
                                          functions::ActivationFunctions_E activationFunction) {


	auto netIterator = ++neurons_.begin();
	auto weightsIterator = ++weights.begin();

	for (; weightsIterator != weights.end();
	       ++netIterator, ++weightsIterator) {

		auto neuronsInLayer = weightsIterator->size() - 1;

		for (unsigned int i = 0; i < neuronsInLayer; ++i)
			netIterator->emplace_back(new neurons::HiddenLayerNeuron(activationFunction));

		netIterator->emplace_back(new neurons::BiasNeuron());
	}


}

template<typename T>
void NeuralNetwork<T>::createConnections() {

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

template<typename T>
void NeuralNetwork<T>::createConnections(NeuralNetwork<T>::weights_t weights) {

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

template<typename T>
std::vector<int> NeuralNetwork<T>::getTopology() const {

	std::vector<int> topology;

	auto outputLayer = --neurons_.end();

	for (auto iterator = ++neurons_.begin(); iterator != outputLayer; ++iterator)
		topology.emplace_back(iterator->size() - 1);

	return topology;
}

template<typename T>
typename NeuralNetwork<T>::weights_t NeuralNetwork<T>::getWeights() const {

	weights_t weights;

	for (auto layer : neurons_) {
		std::vector<std::vector<double>> layerWeights;
		for (auto neuron : layer) {
			auto synapses = neuron->getOutputSynapses();
			std::vector<double> weights;
			for (auto synapse : synapses) {
				weights.push_back(synapse->getWeight());
			}
			layerWeights.emplace_back(std::move(weights));
		}
		weights.emplace_back(std::move(layerWeights));
	}
	weights.pop_back();
	return weights;
}

template<typename T>
double NeuralNetwork<T>::computeResult(const T &datum) {

	feedForward(datum);
	return outputNeuron_->getValue();

}

template<typename T>
void NeuralNetwork<T>::feedForward(const T &datum) {

	setInputs(datum);

	for (std::vector<layer_t>::iterator layerIt = neurons_.begin() + 1; layerIt != neurons_.end(); ++layerIt) {
		for (layer_t::iterator neuronIt = layerIt->begin(); neuronIt != layerIt->end(); ++neuronIt) {
			(*neuronIt)->recalculateValue();
		}
	}

}




template<typename T>
double NeuralNetwork<T>::stochasticGradientDescent(const data_vect_t &inputData,
                                                   int epochs, int batchSize, double eta, int testsPct,
                                                   std::function<void()> updateProgress) {

	std::vector<typename std::vector<T>::const_iterator> dataCopy;
	std::random_device randomDevice;
	std::mt19937 g(randomDevice());

	double factor = eta / batchSize;

	auto testsNumber = inputData.size() * testsPct / 100;
	auto firstTest = (inputData.end() - testsNumber);

	for (auto iterator = inputData.begin(); iterator != firstTest; ++iterator)
		dataCopy.emplace_back(iterator);


	for (int epoch = 0; epoch < epochs; ++epoch) {

		std::shuffle(dataCopy.begin(), dataCopy.end(), g);

		for (auto iterator = dataCopy.begin(); iterator != dataCopy.end(); iterator += batchSize)
//			runBatchAndUpdateWeights(iterator, iterator + batchSize, factor);

		updateProgress();
	}


//	double meanSquaredError = getMSE(firstTest, inputData.end());

//	return (meanSquaredError / testsNumber);

	return 0;
}

//double NeuralNetwork::getMSE(const houses_t::const_iterator &begin,
//                             const houses_t::const_iterator &end) {
//	double meanSquaredError = 0.0;
//
//	for(auto test = begin; test != end; ++test){
//		double currentError = calculateHousesPrice(**test);
//		currentError -= (*test)->getPrice();
//		currentError *= currentError;
//		meanSquaredError += currentError;
//	}
//	return meanSquaredError;
//}

//template<typename T>
//void NeuralNetwork<T>::runBatchAndUpdateWeights(std::vector<data_vect_t::const_iterator>::iterator begin,
//                                                const std::vector<data_vect_t::const_iterator>::iterator end,
//                                                double factor) {
//
//	for (; begin != end; ++begin) {
//
//		feedForward(**begin);
//		calculateOutputError(**begin);
//		propagateBack();
//
//	}
//
//	updateWeights(factor);
//
//}

template <typename T>
void NeuralNetwork<T>::calculateOutputError(const T& datum) {

	double expected = getExpectedResult(datum);
	outputNeuron_->calculateOutputError(expected, costDerivative);
}

template <typename T>
void NeuralNetwork<T>::updateWeights(double factor) {

	for (layer_t layer : neurons_) {
		for (auto neuron : layer) {
			neuron->updateOutputWeights(factor);
		}
	}

}

template <typename T>
void NeuralNetwork<T>::propagateBack() {

	auto inputLayer = --neurons_.rend();

	for (auto layer_it = ++neurons_.rbegin(); layer_it != inputLayer; ++layer_it)
		for (auto neuron_it = layer_it->begin(); neuron_it != layer_it->end(); ++neuron_it)
			(*neuron_it)->computeError();

}

///MARK: Specialized

template<>
void NeuralNetwork<house::NormalizedValuesHouse>::setInputs(const house::NormalizedValuesHouse &datum) {

	layer_t &inputLayer = neurons_.at(0);

	inputLayer.at(0)->setOutputValue(datum.getDate());
	inputLayer.at(1)->setOutputValue(datum.getBedrooms());
	inputLayer.at(2)->setOutputValue(datum.getBathrooms());
	inputLayer.at(3)->setOutputValue(datum.getSqftLiving());
	inputLayer.at(4)->setOutputValue(datum.getSqftLot());
	inputLayer.at(5)->setOutputValue(datum.getFloors());
	inputLayer.at(6)->setOutputValue(datum.getWaterfront());
	inputLayer.at(7)->setOutputValue(datum.getView());
	inputLayer.at(8)->setOutputValue(datum.getCondition());
	inputLayer.at(9)->setOutputValue(datum.getGrade());
	inputLayer.at(10)->setOutputValue(datum.getSqftAbove());
	inputLayer.at(11)->setOutputValue(datum.getSqftBasement());
	inputLayer.at(12)->setOutputValue(datum.getYrBuilt());
	inputLayer.at(13)->setOutputValue(datum.getYrRenovated());
	inputLayer.at(14)->setOutputValue(datum.getZipcode());
	inputLayer.at(15)->setOutputValue(datum.getLat());
	inputLayer.at(16)->setOutputValue(datum.getLong());
	inputLayer.at(17)->setOutputValue(datum.getSqftLiving15());
	inputLayer.at(18)->setOutputValue(datum.getSqftLot15());

}


template<>
void NeuralNetwork<house::NormalizedValuesHouse>::createInputNeurons() {


	// 19 input neurons for each position in a house + 1 bias neuron
	for (int i = 0; i < 19; ++i) {
		neurons_.at(0).emplace_back(new neurons::InputNeuron());
	}
	neurons_.at(0).emplace_back(new neurons::BiasNeuron());

}










