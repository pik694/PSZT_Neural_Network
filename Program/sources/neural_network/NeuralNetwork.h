//Created by Daniel Bigos

#include <vector>

#include "TrainingDataFactory.h"
#include "FileReader.h"

#include "neural_network/neurons/Neuron.h"
#include "house/NormalizedValuesHouse.h"
#include "ActivationFunctionsBank.h"

namespace neural_network {
	class NeuralNetwork {
	public:

		using weights_t = std::vector<std::vector<std::vector<double>>>;

		NeuralNetwork(std::vector<int> neuronsInLayer, functions::ActivationFunctions_E activationFunction);
		NeuralNetwork(weights_t weights, functions::ActivationFunctions_E);


//		double calculatePrice(const  NormalizedValuesHouse& house) {return feedForward(house);}

//		double feedForward(const  NormalizedValuesHouse&);
//
//		void stochasticGradientDescent(const std::vector<NormalizedValuesHouse>& trainingData,
//		                               unsigned int epochs, unsigned int miniBatchSize, double eta,
//		                               std::function<void()> afterEachEpoch);

		virtual ~NeuralNetwork() = default;

	private:

//		using layer_t = std::vector<std::shared_ptr<neurons::Neuron>>;
//
//		void propagateBack(const  NormalizedValuesHouse&);
//
//
//
//		void setInputs(const  NormalizedValuesHouse&);
//		double getNetResult();
//
//		std::vector<layer_t> neurons_;
//
//		void updateWeights();
	};
}
