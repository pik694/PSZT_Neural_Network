//
// Created by daniel on 16.01.18.
//

#ifndef PSZT_NEURAL_NETWORK_K_FOLD_H
#define PSZT_NEURAL_NETWORK_K_FOLD_H

#include "neural_network/NeuralNetworkTopology.h"
#include "house/NormalizedValuesHouse.h"
#include "neural_network/ActivationFunctionsBank.h"
#include "Program.h"



namespace program {
	class K_FOLD : public Program{
		K_FOLD(std::vector<house::NormalizedValuesHouse> &training_data,
		       unsigned k,
		       std::vector< int > &epoch_vec,
		       std::vector< int > &batch_size_vec,
		       std::vector< neural_network::functions::ActivationFunctions_E > &function_vec,
		       std::vector< double > &eta_vec,
		       std::vector< neural_network::Topology_E > &topology_vec);

		void run () override;

		static void trainNeuralNet();

		~K_FOLD() override = default;

	private:
		std::vector<house::NormalizedValuesHouse> trainingData_;
		std::vector< int > epochVec_;
		std::vector< int > batchSizeVec_;
		std::vector< neural_network::functions::ActivationFunctions_E > functionVec_;
		std::vector< double > etaVec_;
		std::vector< neural_network::Topology_E > topologyVec_;
		const unsigned k_ = 0;
	};



}


#endif //PSZT_NEURAL_NETWORK_K_FOLD_H
