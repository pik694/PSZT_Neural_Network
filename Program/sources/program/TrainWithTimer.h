//
// Created by Daniel Bigos
//

#ifndef PSZT_NEURAL_NETWORK_TRAINWITHTIMER_H
#define PSZT_NEURAL_NETWORK_TRAINWITHTIMER_H

#include "Program.h"
#include "neural_network/NeuralNetwork.h"
#include "neural_network/NeuralNetworkTopology.h"
#include "house/NormalizedValuesHouse.h"
#include "neural_network/ActivationFunctionsBank.h"
#include "Serializator.h"

const int TIME = 7;
typedef std::tuple< neural_network::NeuralNetwork<house::NormalizedValuesHouse>, int, const int, const double, const int, double , const neural_network::functions::ActivationFunctions_E, const unsigned > TimerTuple;

namespace program
{
    class TrainWithTimer : public Program
    {
    public:
        TrainWithTimer( std::vector<house::NormalizedValuesHouse> &training_data,
                        unsigned time,
                        std::vector< int > &batch_size_vec,
                        std::vector< neural_network::functions::ActivationFunctions_E > &function_vec,
                        std::vector< double > &eta_vec,
                        std::vector< neural_network::Topology_E > &topology_vec,
                        int percentage,
                        int threads_for_eta );

        void run() override;

        void doTraining();

        static void trainNeuralNet( TimerTuple& config, const std::vector<house::NormalizedValuesHouse> & training_data );

        virtual ~TrainWithTimer();
    private:
        std::vector<house::NormalizedValuesHouse> trainingData_;
        unsigned time_;
        std::vector< int > batchSizeVec_;
        std::vector< neural_network::functions::ActivationFunctions_E > functionVec_;
        std::vector< double > etaVec_;
        std::vector< neural_network::Topology_E > topologyVec_;
        int percentage_;
        int threadsForEta_;
        std::vector< TimerTuple > configVec_;
        unsigned iterations_;
    };
}

#endif //PSZT_NEURAL_NETWORK_TRAINWITHTIMER_H
