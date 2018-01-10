//
// Created by Piotr Żelazko on 06.01.2018.
//

#ifndef PSZT_NEURAL_NETWORK_RANDOMNUMBERGENERATOR_H
#define PSZT_NEURAL_NETWORK_RANDOMNUMBERGENERATOR_H

#include <random>

template <int min, int max>
class RandomNumberGenerator {
public:

	static int generateInteger(){
		static 	std::random_device randomDevice;
		static  std::mt19937 generator;
		static  std::uniform_int_distribution<> distribution (min, max);

		return distribution(generator);
	}

	static double generateDouble(){
		static 	std::random_device randomDevice;
		static  std::mt19937 generator;
		static  std::uniform_real_distribution<> distribution ((double)min,(double)max);

		return distribution(generator);
	}

};

#endif //PSZT_NEURAL_NETWORK_RANDOMNUMBERGENERATOR_H
