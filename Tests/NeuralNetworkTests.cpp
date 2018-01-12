//
// Created by Piotr Żelazko on 10.01.2018.
//

#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/test/unit_test.hpp>
#include "neural_network/NeuralNetwork.h"
#include "neural_network/ActivationFunctionsBank.h"
#include "house/NormalizedValuesHouse.h"


BOOST_AUTO_TEST_SUITE(NEURAL_NETWORK_TESTS)

	using namespace neural_network;
	using NHouse = house::NormalizedValuesHouse;
	using namespace boost::gregorian;
	auto sampleActivationFunction = functions::ActivationFunctions_E::hyperbolicTangent;

	BOOST_AUTO_TEST_CASE(NeuralNetworkCreation) {


		std::vector<int> topology = {1, 2, 3};

		BOOST_CHECK_NO_THROW(NeuralNetwork<NHouse> net (topology, sampleActivationFunction));

	}


	BOOST_AUTO_TEST_CASE(TopologyTest) {


		std::vector<int> topology = {1, 2, 3};

		NeuralNetwork<NHouse> net (topology, sampleActivationFunction);

		auto netTopology = net.getTopology();

		BOOST_CHECK_EQUAL_COLLECTIONS(topology.begin(), topology.end(), netTopology.begin(), netTopology.end());


	}

	BOOST_AUTO_TEST_CASE(CheckWeightsAndTopology) {

		std::vector<int> topology = {1, 2, 3};

		NeuralNetwork<NHouse> net (topology, sampleActivationFunction);

		auto weights = net.getWeights();

		BOOST_CHECK_EQUAL(weights.size(), topology.size() + 1);

		for (unsigned int i = 0; i < topology.size(); ++i)
			BOOST_CHECK_EQUAL(weights.at(i + 1).size() - 1, topology.at(i));

	}


	BOOST_AUTO_TEST_CASE(CheckSecondNetTopology) {

		std::vector<int> topology = {1, 2, 3};

		NeuralNetwork<NHouse> net (topology, sampleActivationFunction);

		auto weights = net.getWeights();

		NeuralNetwork<NHouse> secondNet (topology, sampleActivationFunction);

		auto secondNetTopology = secondNet.getTopology();

		BOOST_CHECK_EQUAL_COLLECTIONS(topology.begin(), topology.end(), secondNetTopology.begin(),
		                              secondNetTopology.end());

	}

	BOOST_AUTO_TEST_CASE(CheckSecondNetWeights) {

//		std::vector<int> topology = {1,2,3};
		std::vector<int> topology = {1};

		NeuralNetwork<NHouse> net (topology, sampleActivationFunction);

		auto weights = net.getWeights();

		NeuralNetwork<NHouse> secondNet (weights, sampleActivationFunction);

		auto secondNetWeights = secondNet.getWeights();

		for (auto layer1 = weights.begin(), layer2 = secondNetWeights.begin();
		     layer1 != weights.end() && layer2 != secondNetWeights.end();
		     ++layer1, ++layer2) {

			for (auto beginNeuron1 = layer1->begin(), beginNeuron2 = layer2->begin();
			     beginNeuron1 != layer1->end() && beginNeuron2 != layer2->end();
			     ++beginNeuron1, ++beginNeuron2) {

				BOOST_CHECK_EQUAL_COLLECTIONS(
						beginNeuron1->begin(), beginNeuron1->end(),
						beginNeuron2->begin(), beginNeuron2->end()
				);

			}

		}

	}


	BOOST_AUTO_TEST_CASE(SimpleFeedForward) {

		std::vector<int> topology = {1, 2, 3};

		house::NormalizedValuesHouse house;

		NeuralNetwork<NHouse> net(topology, sampleActivationFunction);

		auto calculatedPrice = net.computeResult(house);

		BOOST_CHECK_NE(calculatedPrice, 0.0);

	}

	BOOST_AUTO_TEST_CASE(SimpleBackPropagation) {

		std::vector<int> topology = {1, 2, 3};

		std::vector<house::NormalizedValuesHouse> houses(2);

		NeuralNetwork<NHouse> net(topology, sampleActivationFunction);

		auto MSE = net.stochasticGradientDescent(houses, 1, 1, 0.1, 50, []{});

		BOOST_CHECK_NE(MSE, 0.0);

	}




BOOST_AUTO_TEST_SUITE_END()