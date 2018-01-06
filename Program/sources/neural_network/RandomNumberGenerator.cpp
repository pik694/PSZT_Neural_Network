//
// Created by Piotr Żelazko on 06.01.2018.
//

#include "RandomNumberGenerator.h"

using namespace neural_network;

RandomNumberGenerator* RandomNumberGenerator::instance_ = nullptr;

RandomNumberGenerator::RandomNumberGenerator() {
	srand(time(nullptr));
}

RandomNumberGenerator *RandomNumberGenerator::getInstance() {

	if (!instance_){
		instance_ = new RandomNumberGenerator();
	}

	return instance_;

}

template<typename T>
T RandomNumberGenerator::generateNumber(T min, T max) {
	throw std::domain_error("Implementation for this type is not defined");
}

template <>
int RandomNumberGenerator::generateNumber<int>(int min, int max) {

	return (rand() % (max - min)) + min;

}

template <>
double RandomNumberGenerator::generateNumber<double>(double min, double max) {
	//TODO : real number random generator
	const int magnitude = 1000;

	int maxI = (int) max * magnitude;
	int minI = (int) min * magnitude;
	int result = generateNumber(minI, maxI);

	return ((double)result) / magnitude;

}

