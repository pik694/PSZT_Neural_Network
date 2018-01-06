//Created by Daniel Bigos

#include <vector>
#include "TrainingDataFactory.h"
#include "FileReader.h"


namespace neural_network {
	class NeuralNetwork {
	public:
		NeuralNetwork(std::vector<int> neuronsInLayer, std::function<double(double)>  neuronActivationFunction, std::function<double(double)> );

		double calculatePrice(const House&);

		void propagateBack();

		virtual ~NeuralNetwork();

	private:



	};
}
