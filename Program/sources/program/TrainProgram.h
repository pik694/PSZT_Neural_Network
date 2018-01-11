// Created by Daniel Bigos

#ifndef PSZT_NEURAL_NETWORK_TRAINPROGRAM_H
#define PSZT_NEURAL_NETWORK_TRAINPROGRAM_H

#include <tuple>
#include "Program.h"
#include "neural_network/NeuralNetworkTopology.h"
#include "house/NormalizedValuesHouse.h"
#include "neural_network/ActivationFunctionsBank.h"
#include "Serializator.h"

const int NEURAL_NETWORK = 0;
const int EPOCHS = 1;
const int BATCH_SIZE = 2;
const int ETA = 3;
const int TEST_PERCENTAGE = 4;
const int MSE = 5;
const int ACTIVATION_FUNCTION = 6;

typedef std::tuple< neural_network::NeuralNetwork, const int, const int, const double, const int, double , const neural_network::functions::ActivationFunctions_E > ConfigTuple;

namespace program
{
    class TrainProgram : public Program
    {
    public:
        TrainProgram( std::vector< std::shared_ptr< house::NormalizedValuesHouse > > &training_data,
                      std::vector< int > &epoch_vec,
                      std::vector< int > &batch_size_vec,
                      std::vector< neural_network::functions::ActivationFunctions_E > &function_vec,
                      std::vector< double > &eta_vec,
                      std::vector< neural_network::Topology_E > &topology_vec,
                      int percentage,
                      int threads_for_eta );

        void run() override;

        void doTraining();

        static void trainNeuralNet( ConfigTuple& config, const std::vector< std::shared_ptr< house::NormalizedValuesHouse > > & training_data );

        virtual ~TrainProgram();
    private:
        std::vector< std::shared_ptr< house::NormalizedValuesHouse > > trainingData_;
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
