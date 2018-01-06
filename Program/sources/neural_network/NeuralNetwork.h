//Created by Daniel Bigos

#include <vector>
#include "TrainingDataFactory.h"
#include "FileReader.h"


namespace neural_network {
	class NeuralNetwork {
	private:
	public:
		NeuralNetwork();

		void trainOnFile();

		~NeuralNetwork();
	};
}
