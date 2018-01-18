//
// Created by daniel on 16.01.18.
//

#include "K_FOLD.h"
#include "progress/ProgressStatusManager.h"
#include "neural_network/NeuralNetworkTopology.h"

using namespace program;
using namespace neural_network;
using namespace progress;

using NHouse = house::NormalizedValuesHouse;

K_FOLD::K_FOLD(std::vector<house::NormalizedValuesHouse> &training_data, unsigned k, std::vector<int> &epoch_vec,
               std::vector<int> &batch_size_vec,
               std::vector<neural_network::functions::ActivationFunctions_E> &function_vec,
               std::vector<double> &eta_vec, std::vector<neural_network::Topology_E> &topology_vec) :
		trainingData_(training_data),
		epochVec_(epoch_vec),
		batchSizeVec_(batch_size_vec),
		functionVec_(function_vec),
		etaVec_(eta_vec),
		topologyVec_(topology_vec),
		k_(k) {}


void K_FOLD::run() {

	std::vector<ConfigTuple> configVec;


	for (auto it_topology = topologyVec_.begin(); it_topology != topologyVec_.end(); ++it_topology) {
		for (auto it_epoch = epochVec_.begin(); it_epoch != epochVec_.end(); ++it_epoch) {
			for (auto it_batch_size = batchSizeVec_.begin(); it_batch_size != batchSizeVec_.end(); ++it_batch_size) {
				for (auto it_function = functionVec_.begin(); it_function != functionVec_.end(); ++it_function) {
					for (auto it_eta = etaVec_.begin(); it_eta != etaVec_.end(); ++it_eta) {
						for (unsigned threads_count = 0; threads_count < k_; ++threads_count) {
							NeuralNetwork<NHouse> neural_network(TopologyBank::getTopology(*it_topology), *it_function);
							configVec.emplace_back(neural_network, *it_epoch, *it_batch_size, *it_eta, k_,
							                       std::numeric_limits<double>::max(), *it_function, threads_count);
						}
					}
				}
			}
		}
	}

	while (!configVec.empty()) {

		unsigned iterations = 0;
		std::vector<ConfigTuple> tmpVector;

		for (int i = 0; i < k_; ++i) {
			iterations += std::get<EPOCHS>(configVec.back());
			tmpVector.emplace_back(configVec.back());
			configVec.pop_back();
		}

		setThreads(static_cast<int>(tmpVector.size()));
		ProgressStatusManager::getInstance()->init("Training neural network", iterations);
		for (auto it = tmpVector.begin(); it != tmpVector.end(); ++it)
			threadsVec_.emplace_back(trainNeuralNet, std::ref(*it), std::ref(trainingData_));

		while (getThreads()) {
			ProgressStatusManager::getInstance()->refresh();
			sleep(SLEEP_TIME);
		}

		for (auto it_t = threadsVec_.begin(); it_t != threadsVec_.end(); ++it_t)
			it_t->join();

		ProgressStatusManager::getInstance()->deinit();

		double averageError = 0.0;

		for (auto it = tmpVector.begin(); it != tmpVector.end(); ++it) {
			Serializator<house::NormalizedValuesHouse>::getInstance().serialize(
					std::get<NEURAL_NETWORK>(*it),
					std::get<ACTIVATION_FUNCTION>(*it),
					std::get<EPOCHS>(*it),
					std::get<BATCH_SIZE>(*it),
					std::get<ETA>(*it),
					std::get<K>(*it),
					std::get<MSE>(*it)
			);

			averageError += std::get<MSE>(*it);
		}

		averageError /= k_;

		std::cout << "Average error of a batch : " << averageError << std::endl;

		threadsVec_.clear();

	}


}

void K_FOLD::trainNeuralNet(ConfigTuple &config,
const std::vector<house::NormalizedValuesHouse> &training_data) {

	std::vector <house::NormalizedValuesHouse> data;

	int threadIndex = std::get<INDEX>(config);
	int k = std::get<K>(config);

	for (int i = 0; i < training_data.size(); ++i)
		if (i % k != threadIndex)
			data.push_back(training_data.at(i));

	for (int  i = threadIndex; i < training_data.size(); i += k)
		data.push_back(training_data.at(i));


	int testsPct = 100 / k;


	std::get<MSE>(config) = std::get<NEURAL_NETWORK>(config).stochasticGradientDescent(data,
	                                                                                   std::get<EPOCHS>(config),
	                                                                                   std::get<BATCH_SIZE>(config),
	                                                                                   std::get<ETA>(config),
	                                                                                   testsPct);
	decrementThreads();


}
