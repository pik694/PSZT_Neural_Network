//Created by Daniel Bigos

#include <vector>

#include "house/NormalizedValuesHouse.h"
#include "ActivationFunctionsBank.h"
#include "neurons/Neuron.h"

namespace neural_network {
	class NeuralNetwork {
	public:

		using weights_t = std::vector<std::vector<std::vector<double>>>;

		NeuralNetwork(std::vector<int> topology, functions::ActivationFunctions_E activationFunction);
		NeuralNetwork(weights_t weights, functions::ActivationFunctions_E activationFunction);

		std::vector<int> getTopology();
		weights_t getWeights();

		virtual ~NeuralNetwork() = default;

	private:

		using layer_t = std::vector<std::shared_ptr<neurons::Neuron>>;
		std::vector<layer_t> neurons_;

		void createInputNeurons();
		void createOutputNeuron();
		void createHiddenLayers(std::vector<int>, functions::ActivationFunctions_E);
		void createHiddenLayers(weights_t, functions::ActivationFunctions_E);

		void createConnections();
		void createConnections(weights_t);


	};
}
