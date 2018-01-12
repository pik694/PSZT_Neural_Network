//Created by Daniel Bigos

#ifndef _PSZT_NEURAL_NETWORK
#define _PSZT_NEURAL_NETWORK

#include <vector>

#include "ActivationFunctionsBank.h"
#include "neurons/Neuron.h"
#include "neurons/OutputNeuron.h"
#include "progress/ProgressStatusManager.h"

namespace neural_network {

	template<typename T>
	class NeuralNetwork {
	public:

		using weights_t = std::vector<std::vector<std::vector<double>>>;
		using data_vect_t = std::vector<T>;

		NeuralNetwork(std::vector<int> topology, functions::ActivationFunctions_E activationFunction);

		NeuralNetwork(weights_t weights, functions::ActivationFunctions_E activationFunction);

		std::vector<int> getTopology() const;

		weights_t getWeights() const;

		double stochasticGradientDescent(const data_vect_t &inputData,
		                                 int epochs, int batchSize, double eta, int testsPct,
		                                 std::function<void()> updateProgress = defaultUpdateProgress);

		double computeResult(const T &datum);

		virtual ~NeuralNetwork() = default;

	private:

		using layer_t = std::vector<std::shared_ptr<neurons::Neuron>>;

		std::vector<layer_t> neurons_;
		std::shared_ptr<neurons::OutputNeuron> outputNeuron_;

		void createInputNeurons();

		void createOutputNeuron(functions::ActivationFunctions_E);

		void createHiddenLayers(std::vector<int>, functions::ActivationFunctions_E);

		void createHiddenLayers(weights_t, functions::ActivationFunctions_E);

		void createConnections();

		void createConnections(weights_t);

//		void
//		runBatchAndUpdateWeights(data_vect_t::const_iterator begin, data_vect_t::const_iterator end, double factor);

		void updateWeights(double factor);

		void propagateBack();

		void calculateOutputError(const T &datum);

		void feedForward(const T &datum);

		void setInputs(const T &datum);

		double getExpectedResult(const T &datum);

		static double costDerivative (double received, double expected) {
			return received - expected;
		};

		static void defaultUpdateProgress () {
			progress::ProgressStatusManager::getInstance()->addProgress(1);
		};

//		double getMSE(const std::vector<data_vect_t::const_iterator>::iterator &begin,
//		              const std::vector<data_vect_t::const_iterator>::iterator &end); //TODO: probably this type is incorrect
	};
}

#endif