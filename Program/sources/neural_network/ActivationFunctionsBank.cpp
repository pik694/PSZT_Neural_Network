//
// Created by Marcin Dziedzic on 06/01/2018.
//

#include <string>
#include <map>
#include <boost/program_options.hpp>
#include "ActivationFunctionsBank.h"

using namespace neural_network::functions;

double ActivationFunctionsBank::stepFunction(double x) {
	if (x < 0.5) {
		return 0;
	} else {
		return 1;
	}
}

double ActivationFunctionsBank::stepFunctionDerivative(double x) {
	return 0;
}

double ActivationFunctionsBank::fastSigmoidFunction(double x) {
	return x / (1 + abs(x));
}

double ActivationFunctionsBank::fastSigmoidFunctionDerivative(double x) {
	return 1 / pow(abs(x) + 1, 2);
}

double ActivationFunctionsBank::logisticFunction(double x) {
	return 1 / (1 + pow(EULER_NUMBER, -x));
}

double ActivationFunctionsBank::logisticFunctionDerivative(double x) {
	return pow(EULER_NUMBER, x) / pow((pow(EULER_NUMBER, x) + 1), 2);
}

double ActivationFunctionsBank::hyperbolicTangentFunction(double x) {
	return tanh(x);
}

double ActivationFunctionsBank::hyperbolicTangentFunctionDerivative(double x) {
	return 1.0 - x * x;
}

double ActivationFunctionsBank::specificAlgebraicFunction(double x) {
	return x / sqrt(1 + pow(x, 2));
}

double ActivationFunctionsBank::specificAlgebraicFunctionDerivative(double x) {
	return 1 / pow((pow(x, 2) + 1), 3 / 2);
}

std::pair<std::function<double(double)>, std::function<double(double)>>
ActivationFunctionsBank::getFunctionAndDerivative(ActivationFunctions_E funcEnum) {

	using enum_function_map_t = std::map<ActivationFunctions_E, std::pair<std::function<double(
			double)>, std::function<double(double)>>>;

	static const enum_function_map_t map = {
			{ActivationFunctions_E::step,              std::make_pair(stepFunction, stepFunctionDerivative)},
			{ActivationFunctions_E::fastSigmoid,       std::make_pair(fastSigmoidFunction,
			                                                          fastSigmoidFunctionDerivative)},
			{ActivationFunctions_E::logistic,          std::make_pair(logisticFunction, logisticFunctionDerivative)},
			{ActivationFunctions_E::hyperbolicTangent, std::make_pair(hyperbolicTangentFunction,
			                                                          hyperbolicTangentFunctionDerivative)},
			{ActivationFunctions_E::specificAlgebraic, std::make_pair(specificAlgebraicFunction,
			                                                          specificAlgebraicFunctionDerivative)},
	};

	return map.at(funcEnum);

}

namespace boost {
	template<>
	ActivationFunctions_E lexical_cast(const std::string &name) {

		using string_function_map_t = std::map<const std::string, ActivationFunctions_E>;

		static const string_function_map_t map = {
				{std::to_string(static_cast<int>(ActivationFunctions_E::step)),              ActivationFunctions_E::step},
				{std::to_string(
						static_cast<int>(ActivationFunctions_E::fastSigmoid)),               ActivationFunctions_E::fastSigmoid},
				{std::to_string(
						static_cast<int>(ActivationFunctions_E::logistic)),                  ActivationFunctions_E::logistic},
				{std::to_string(
						static_cast<int>(ActivationFunctions_E::hyperbolicTangent)),         ActivationFunctions_E::hyperbolicTangent},
				{std::to_string(
						static_cast<int>(ActivationFunctions_E::specificAlgebraic)),         ActivationFunctions_E::specificAlgebraic}
		};

		return map.at(name);
	}

}
