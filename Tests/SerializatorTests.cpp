//
// Created by Piotr Żelazko on 11.01.2018.
//


#include <boost/test/unit_test.hpp>
#include "neural_network/NeuralNetwork.h"
#include "Serializator.h"

using namespace neural_network;

BOOST_AUTO_TEST_SUITE(SerializatorTests)

	BOOST_AUTO_TEST_CASE(SimpleFileWriting) {

		NeuralNetwork net({1,2,3,}, functions::ActivationFunctions_E::step);

		Serializator::getInstance().setOutputDirectory("./");

		BOOST_CHECK_NO_THROW(Serializator::getInstance().serialize(net,functions::ActivationFunctions_E::step, 1, 1, 0.1, 10, 0.50));

	}

	BOOST_AUTO_TEST_CASE(TwoFileWritings) {

		NeuralNetwork net({1,2,3,}, functions::ActivationFunctions_E::step);

		Serializator::getInstance().setOutputDirectory("./");

		BOOST_CHECK_NO_THROW(Serializator::getInstance().serialize(net,functions::ActivationFunctions_E::step, 1, 1, 0.1, 10, 0.50));
		BOOST_CHECK_NO_THROW(Serializator::getInstance().serialize(net,functions::ActivationFunctions_E::step, 1, 1, 0.1, 10, 0.50));
	}


BOOST_AUTO_TEST_SUITE_END()
