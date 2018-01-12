//Created by Daniel Bigos

#ifndef _PSZT_NEURAL_NETWORK
#define _PSZT_NEURAL_NETWORK

#include <vector>
#include <random>

#include "ActivationFunctionsBank.h"
#include "neurons/Neuron.h"
#include "neurons/OutputNeuron.h"
#include "progress/ProgressStatusManager.h"
#include "neurons/HiddenLayerNeuron.h"
#include "neurons/BiasNeuron.h"

namespace neural_network {

	template<typename T>
	class NeuralNetwork {
	public:

		using weights_t = std::vector<std::vector<std::vector<double>>>;
		using data_vect_t = std::vector<T>;

		NeuralNetwork(std::vector<int> topology, functions::ActivationFunctions_E activationFunction) :
				neurons_(topology.size() + 2) {

			createInputNeurons();

			createHiddenLayers(topology, activationFunction);

			createOutputNeuron(activationFunction);

			createConnections();

		}

		NeuralNetwork(weights_t weights, functions::ActivationFunctions_E activationFunction) :
				neurons_(weights.size() + 1) {

			createInputNeurons();

			createHiddenLayers(weights, activationFunction);

			createOutputNeuron(activationFunction);

			createConnections(weights);
		}

		std::vector<int> getTopology() const {

			std::vector<int> topology;

			auto outputLayer = --neurons_.end();

			for (auto iterator = ++neurons_.begin(); iterator != outputLayer; ++iterator)
				topology.emplace_back(iterator->size() - 1);

			return topology;
		}

		weights_t getWeights() const {

			weights_t weights;

			for (auto layer : neurons_) {
				std::vector<std::vector<double>> layerWeights;
				for (auto neuron : layer) {
					auto synapses = neuron->getOutputSynapses();
					std::vector<double> weights;
					for (auto synapse : synapses) {
						weights.push_back(synapse->getWeight());
					}
					layerWeights.emplace_back(std::move(weights));
				}
				weights.emplace_back(std::move(layerWeights));
			}
			weights.pop_back();
			return weights;
		}

		double stochasticGradientDescent(const data_vect_t &inputData,
		                                 int epochs, int batchSize, double eta, int testsPct,
		                                 std::function<void()> updateProgress = defaultUpdateProgress) {


			double factor = eta / batchSize;

			auto testsNumber = inputData.size() * testsPct / 100;
			auto firstTest = (inputData.end() - testsNumber);

			std::vector<std::reference_wrapper<const T>> dataCopy(inputData.begin(), firstTest);
			std::random_device randomDevice;
			std::mt19937 g(randomDevice());

			for (int epoch = 0; epoch < epochs; ++epoch) {

				std::shuffle(dataCopy.begin(), dataCopy.end(), g);

				for (auto iterator = dataCopy.begin(); iterator != dataCopy.end();) {
					for (int i = 0; i < batchSize && iterator != dataCopy.end(); ++iterator, ++i) {
						feedForward(*iterator);
						calculateOutputError(*iterator);
						propagateBack();
					}
					updateWeights(factor);
				}

				updateProgress();
			}


			double meanSquaredError = 0.0;

			for (auto test = firstTest; test != inputData.end(); ++test) {
				double currentError = computeResult(*test);
				currentError -= getExpectedResult(*test);
				currentError *= currentError;
				meanSquaredError += currentError;
			}

			return (meanSquaredError / testsNumber);

			return 0;
		}


		double computeResult(const T &datum) {

			feedForward(datum);
			return outputNeuron_->getValue();

		}

		virtual ~NeuralNetwork() = default;

	private:

		using layer_t = std::vector<std::shared_ptr<neurons::Neuron>>;

		std::vector<layer_t> neurons_;
		std::shared_ptr<neurons::OutputNeuron> outputNeuron_;

		void createInputNeurons();

		void createOutputNeuron(functions::ActivationFunctions_E functions) {

			// output layer consists of only one output neuron
			outputNeuron_ = std::make_shared<neurons::OutputNeuron>(functions);
			neurons_.at(neurons_.size() - 1).emplace_back(outputNeuron_);

		}

		void createHiddenLayers(std::vector<int> topology, functions::ActivationFunctions_E activationFunction) {

			// hidden layers with number of neurons specified in the input argument + 1 bias neuron per layer

			auto hiddenLayers = topology.size();

			for (unsigned int i = 0; i < hiddenLayers; ++i) {
				for (int j = 0; j < topology.at(i); ++j) {
					neurons_.at(i + 1).emplace_back(new neurons::HiddenLayerNeuron(activationFunction));
				}
				neurons_.at(i + 1).emplace_back(new neurons::BiasNeuron());
			}

		}

		void createHiddenLayers(weights_t weights, functions::ActivationFunctions_E activationFunction) {


			auto netIterator = ++neurons_.begin();
			auto weightsIterator = ++weights.begin();

			for (; weightsIterator != weights.end();
			       ++netIterator, ++weightsIterator) {

				auto neuronsInLayer = weightsIterator->size() - 1;

				for (unsigned int i = 0; i < neuronsInLayer; ++i)
					netIterator->emplace_back(new neurons::HiddenLayerNeuron(activationFunction));

				netIterator->emplace_back(new neurons::BiasNeuron());
			}


		}

		void createConnections() {
			for (auto i = neurons_.begin(), j = i + 1; j != neurons_.end(); ++i, ++j) {
				for (auto k = i->begin(); k != i->end(); ++k) {
					for (auto l = j->begin(); l != j->end(); ++l) {
						bool validConnection = false;
						try {
							auto _ = dynamic_cast<neurons::BiasNeuron &>(**l);

						} catch (std::bad_cast &) {
							validConnection = true;
						}
						if (validConnection) {
							auto synapse = std::make_shared<neurons::Synapse>(*k, *l);
							(*k)->addOutputSynapse(synapse);
							(*l)->addInputSynapse(synapse);
						}

					}
				}
			}
		}

		void createConnections(weights_t weights) {

			auto layerIt = weights.begin();
			auto i = neurons_.begin();
			auto j = i + 1;

			for (; j != neurons_.end(); ++i, ++j, ++layerIt) {

				auto k = i->begin();
				auto weightK = layerIt->begin();

				for (; k != i->end(); ++k, ++weightK) {
					auto l = j->begin();
					auto weightsL = weightK->begin();
					for (; l != j->end() && weightsL != weightK->end(); ++l, ++weightsL) {

						auto synapse = std::make_shared<neurons::Synapse>(*k, *l, *weightsL);

						(*k)->addOutputSynapse(synapse);
						(*l)->addInputSynapse(synapse);
					}
				}
			}

		}

		void updateWeights(double factor) {

			for (layer_t layer : neurons_) {
				for (auto neuron : layer) {
					neuron->updateOutputWeights(factor);
				}
			}

		}

		void propagateBack() {

			auto inputLayer = --neurons_.rend();

			for (auto layer_it = ++neurons_.rbegin(); layer_it != inputLayer; ++layer_it)
				for (auto neuron_it = layer_it->begin(); neuron_it != layer_it->end(); ++neuron_it)
					(*neuron_it)->computeError();

		}

		void calculateOutputError(const T &datum) {

			double expected = getExpectedResult(datum);
			outputNeuron_->calculateOutputError(expected, costDerivative);
		}

		void feedForward(const T &datum) {

			setInputs(datum);

			for (std::vector<layer_t>::iterator layerIt = neurons_.begin() + 1; layerIt != neurons_.end(); ++layerIt) {
				for (layer_t::iterator neuronIt = layerIt->begin(); neuronIt != layerIt->end(); ++neuronIt) {
					(*neuronIt)->recalculateValue();
				}
			}

		}

		void setInputs(const T &datum);

		double getExpectedResult(const T &datum);

		static double costDerivative(double received, double expected) {
			return received - expected;
		};

		static void defaultUpdateProgress() {
			progress::ProgressStatusManager::getInstance()->addProgress(1);
		};

	};
}

#endif