//
// Created by Piotr Żelazko on 06.01.2018.
//

#ifndef PSZT_NEURAL_NETWORK_RANDOMNUMBERGENERATOR_H
#define PSZT_NEURAL_NETWORK_RANDOMNUMBERGENERATOR_H

#include <stdexcept>

namespace neural_network {
	class RandomNumberGenerator {
	public:
		static RandomNumberGenerator* getInstance();

		template<typename T>
		T generateNumber(T min, T max);

	private:
		RandomNumberGenerator();

		static RandomNumberGenerator *instance_;
	};

}


#endif //PSZT_NEURAL_NETWORK_RANDOMNUMBERGENERATOR_H
