// Created by Daniel Bigos

#ifndef PSZT_NEURAL_NETWORK_TRAINPROGRAM_H
#define PSZT_NEURAL_NETWORK_TRAINPROGRAM_H

#include "Program.h"

namespace program
{
    class TrainProgram : public Program
    {
    public:
        TrainProgram( std::vector<house::NormalizedValuesHouse> &training_data,
                      std::vector< int > &epoch_vec,
                      std::vector< int > &batch_size_vec,
                      std::vector< neural_network::functions::ActivationFunctions_E > &function_vec,
                      std::vector< double > &eta_vec,
                      std::vector< neural_network::Topology_E > &topology_vec,
                      int percentage,
                      int threads_for_eta );

        void run() override;

        void doTraining();

        static void trainNeuralNet( ConfigTuple& config, const std::vector<house::NormalizedValuesHouse> & training_data );

        virtual ~TrainProgram();
    private:
        std::vector<house::NormalizedValuesHouse> trainingData_;
        std::vector< int > epochVec_;
        std::vector< int > batchSizeVec_;
        std::vector< neural_network::functions::ActivationFunctions_E > functionVec_;
        std::vector< double > etaVec_;
        std::vector< neural_network::Topology_E > topologyVec_;
        int percentage_;
        int threadsForEta_;
        std::vector< ConfigTuple > configVec_;
        unsigned iterations_;
    };
}

#endif //PSZT_NEURAL_NETWORK_TRAINPROGRAM_H
