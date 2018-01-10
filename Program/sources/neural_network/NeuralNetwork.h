//Created by Daniel Bigos

#include <vector>

#include "house/NormalizedValuesHouse.h"
#include "ActivationFunctionsBank.h"
#include "neurons/Neuron.h"
#include "neurons/OutputNeuron.h"

namespace neural_network {
	class NeuralNetwork {
	public:

		using weights_t = std::vector<std::vector<std::vector<double>>>;
		using houses_t = std::vector<house::NormalizedValuesHouse>;

		NeuralNetwork(std::vector<int> topology, functions::ActivationFunctions_E activationFunction);
		NeuralNetwork(weights_t weights, functions::ActivationFunctions_E activationFunction);

		std::vector<int> getTopology() const;
		weights_t getWeights() const;

		void stochasticGradientDescent(const houses_t& inputHouses, int epochs, int batchSize, double eta, std::function<void()> updateProgress);

		double calculateHousesPrice(const house::NormalizedValuesHouse& house);

		virtual ~NeuralNetwork() = default;

	private:

		using layer_t = std::vector<std::shared_ptr<neurons::Neuron>>;
		using houses_const_iterator_t = std::vector<houses_t::const_iterator>::iterator;
		std::vector<layer_t> neurons_;
		std::shared_ptr<neurons::OutputNeuron> outputNeuron_;

		void createInputNeurons();
		void createOutputNeuron(functions::ActivationFunctions_E);
		void createHiddenLayers(std::vector<int>, functions::ActivationFunctions_E);
		void createHiddenLayers(weights_t, functions::ActivationFunctions_E);

		void createConnections();
		void createConnections(weights_t);


		void runBatchAndUpdateWeights(houses_const_iterator_t begin, houses_const_iterator_t end, double eta, int batchSize);
		void updateWeights(double eta, int batchSize);
		void propagateBack();
		void calculateOutputError(const house::NormalizedValuesHouse& house);

		void feedForward(const house::NormalizedValuesHouse& house);
		void setInputs(const house::NormalizedValuesHouse& house);

		const std::function<double (double, double)> costDerivative = [](double received, double expected){return received - expected;};
	};
}
