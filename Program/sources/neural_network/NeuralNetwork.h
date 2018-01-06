//Created by Daniel Bigos

#include <vector>
#include "TrainingDataFactory.h"
#include "FileReader.h"


namespace neural_network {
	class NeuralNetwork {
	private:
	public:
		NeuralNetwork(std::vector<int> neuronsInLayer, std::function<double(double)>  neuronActivationFunction, std::function<double(double)> );

		virtual ~NeuralNetwork();
	};
}
