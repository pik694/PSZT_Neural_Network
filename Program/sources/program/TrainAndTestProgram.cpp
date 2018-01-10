#include "TrainAndTestProgram.h"

using namespace program;

void TrainAndTestProgram::run()
{
    for( auto it_topology = topologyVec_.begin(); it_topology != topologyVec_.end(); ++it_topology )
    {
        for( auto it_epoch = epochVec_.begin(); it_epoch != epochVec_.end(); ++it_epoch )
        {
            for( auto it_pack = packVec_.begin(); it_pack != packVec_.end(); ++it_pack )
            {
                for( auto it_eta = etaVec_.begin(); it_eta != etaVec_.end(); ++it_eta )
                {
                    for( auto it_function = functionVec_.begin(); it_function != functionVec_.end(); ++it_function )
                    {
                        //TODO  train
                    }
                }
            }
        }
    }

    //TODO test
}

TrainAndTestProgram::TrainAndTestProgram( std::vector< std::shared_ptr< house::NormalizedValuesHouse > > *training_data,
                                         std::vector< int > *epoch_vec, std::vector< int > *pack_vec,
                                         std::vector< neural_network::functions::ActivationFunctions_E > *function_vec,
                                         std::vector< double > *eta_vec,
                                         std::vector <neural_network::Topology_E > *topology_vec,
                                         std::vector< int > *tolerance_vec )
{
    trainingData_ = std::move( *training_data );
    epochVec_ = std::move( *epoch_vec );
    packVec_ = std::move( *pack_vec );
    functionVec_ = std::move( *function_vec );
    etaVec_ = std::move( *eta_vec );
    topologyVec_ = std::move( *topology_vec );
    toleranceVec_ = std::move( *tolerance_vec );
}

