// Created by Daniel Bigos

#ifndef PSZT_NEURAL_NETWORK_TRAINANDTESTPROGRAM_H
#define PSZT_NEURAL_NETWORK_TRAINANDTESTPROGRAM_H

#include "Program.h"
#include "neural_network/NeuralNetworkTopology.h"
#include "house/NormalizedValuesHouse.h"
#include "neural_network/ActivationFunctionsBank.h"

namespace program
{
    class TrainAndTestProgram : public Program
    {
    public:
        TrainAndTestProgram( std::vector< std::shared_ptr< house::NormalizedValuesHouse > > *training_data,
                             std::vector< int > *epoch_vec, std::vector< int > *pack_vec,
                             std::vector< neural_network::functions::ActivationFunctions_E >* function_vec,
                             std::vector< double >* eta_vec, std::vector< neural_network::Topology_E >* topology_vec,
                             std::vector< int >* tolerance_vec );
        void run() override;

        ~TrainAndTestProgram() override = default;

    private:
        std::vector< std::shared_ptr< house::NormalizedValuesHouse > > trainingData_;
        std::vector< int > epochVec_;
        std::vector< int > packVec_;
        std::vector< neural_network::functions::ActivationFunctions_E > functionVec_;
        std::vector< double > etaVec_;
        std::vector< neural_network::Topology_E > topologyVec_;
        std::vector< int > toleranceVec_;
    };
}

#endif //PSZT_NEURAL_NETWORK_TRAINANDTESTPROGRAM_H
