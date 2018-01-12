//
// Created by Piotr Żelazko on 11.01.2018.
//


#include <boost/test/unit_test.hpp>
#include "neural_network/NeuralNetwork.h"
#include "house/NormalizedValuesHouse.h"
#include <fstream>
#include "Serializator.h"



using NHouse = house::NormalizedValuesHouse;
using namespace neural_network;

BOOST_AUTO_TEST_SUITE(SerializatorTests)

	BOOST_AUTO_TEST_CASE(SimpleFileWriting) {

		NeuralNetwork<NHouse > net({1,2,3,}, functions::ActivationFunctions_E::step);

		Serializator<NHouse>::getInstance().setOutputDirectory("./serialized_nets/");

		BOOST_CHECK_NO_THROW(Serializator<NHouse>::getInstance().serialize(net,functions::ActivationFunctions_E::step, 1, 1, 0.1, 10, 0.50));

	}

	BOOST_AUTO_TEST_CASE(TwoFileWritings) {

		NeuralNetwork<NHouse> net({1,2,3,}, functions::ActivationFunctions_E::step);

		Serializator<NHouse>::getInstance().setOutputDirectory("./serialized_nets/");

		BOOST_CHECK_NO_THROW(Serializator<NHouse>::getInstance().serialize(net,functions::ActivationFunctions_E::step, 1, 1, 0.1, 10, 0.50));
		BOOST_CHECK_NO_THROW(Serializator<NHouse>::getInstance().serialize(net,functions::ActivationFunctions_E::step, 1, 1, 0.1, 10, 0.50));
	}

	BOOST_AUTO_TEST_CASE(Deserialization) {

		std::vector<int> topology = {1,2,3};

		Serializator<NHouse>::getInstance().setOutputDirectory("./serialized_nets/");

		std::ifstream stream ("./serialized_nets/deserializable.nnet");

		BOOST_REQUIRE(stream.is_open());


		auto net1 = Serializator<NHouse>::getInstance().deserialize(stream);

		stream.close();

		auto netTopology = net1.getTopology();

		BOOST_CHECK_EQUAL_COLLECTIONS(topology.begin(), topology.end(),
		                              netTopology.begin(), netTopology.end());

	}


BOOST_AUTO_TEST_SUITE_END()
