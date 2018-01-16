//
// Created by daniel on 16.01.18.
//

#include "K_FOLD.h"
#include "progress/ProgressStatusManager.h"
#include "neural_network/NeuralNetwork.h"

using namespace program;
using namespace progress;

K_FOLD::K_FOLD(std::vector<house::NormalizedValuesHouse> &training_data, unsigned k, std::vector<int> &epoch_vec,
               std::vector<int> &batch_size_vec,
               std::vector<neural_network::functions::ActivationFunctions_E> &function_vec,
               std::vector<double> &eta_vec, std::vector<neural_network::Topology_E> &topology_vec):
		trainingData_(training_data),
		epochVec_(epoch_vec),
		batchSizeVec_(batch_size_vec),
		functionVec_(function_vec),
		etaVec_(eta_vec),
		topologyVec_(topology_vec),
		k_(k) {}


void K_FOLD::run() {
	using NN_t = neural_network::NeuralNetwork<house::NormalizedValuesHouse>;
	using config_t = std::tuple<std::vector<house::NormalizedValuesHouse>,
			int, int,neural_network::functions::ActivationFunctions_E,
			double, neural_network::Topology_E, unsigned>;

	std::vector<config_t > configVect;

	for (auto& epoch : epochVec_)
		for(auto& batch : batchSizeVec_)
			for(auto& function : functionVec_)
				for(auto& eta : etaVec_)
					for(auto& topology : topologyVec_)
						configVect.emplace_back(std::make_tuple(trainingData_ ,epoch,
						                                     batch, function,
						                                     eta, topology, k_));


	while (!configVect.empty()){
		int iterations = 0;
		std::vector<config_t> tmpConfigVect;
		std::vector<std::thread> threads;

		for (int i = 0; i < THREADS_COUNT && !configVect.empty(); ++i){
			iterations += std::get<1>(configVect.back())*k_;
			tmpConfigVect.emplace_back(std::move(configVect.back()));
			configVect.pop_back();
		}

		setThreads(static_cast<int>(tmpConfigVect.size()));
		ProgressStatusManager::getInstance()->init("Training neural network", iterations);

		for (auto it = tmpConfigVect.begin(); it != tmpConfigVect.end(); ++it)
			threads.emplace_back(trainNeuralNet, std::ref(*it));


		while(getThreads()){
			ProgressStatusManager::getInstance()->refresh();
			sleep(SLEEP_TIME);
		}

		for (auto it = threads.begin(); it != threads.end(); ++it)
			it->join();

		ProgressStatusManager::getInstance()->deinit();

		for (auto it = tmpConfigVect.begin(); it != tmpConfigVect.end(); ++it){


		}

	}
}
