#include <boost/range/adaptor/reversed.hpp>



#include "NeuralNetwork.h"
#include "neurons/InputNeuron.h"
#include "neurons/BiasNeuron.h"
#include "neurons/HiddenLayerNeuron.h"
#include "progress/ProgressStatusManager.h"

using namespace neural_network;


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

template<>
double NeuralNetwork<house::NormalizedValuesHouse>::getExpectedResult(const house::NormalizedValuesHouse &datum) {
	return datum.getPrice();
}

template<>
double NeuralNetwork<std::pair<bool, bool>>::getExpectedResult(const std::pair<bool, bool> &datum) {
	return ((int)datum.first + (int)datum.second) % 2;
}

template<>
void NeuralNetwork<std::pair<bool, bool>>::createInputNeurons() {


	// 2 input neurons for each position in a house + 1 bias neuron
	for (int i = 0; i < 2; ++i) {
		neurons_.at(0).emplace_back(new neurons::InputNeuron());
	}
	neurons_.at(0).emplace_back(new neurons::BiasNeuron());

}

template<>
void NeuralNetwork<std::pair<bool, bool>>::setInputs(const std::pair<bool, bool> &datum) {
	layer_t &inputLayer = neurons_.at(0);

	inputLayer.at(0)->setOutputValue(datum.first);
	inputLayer.at(0)->setOutputValue(datum.second);
}
