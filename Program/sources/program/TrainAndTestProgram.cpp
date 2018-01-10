#include "TrainAndTestProgram.h"
#include "Serializator.h"

using namespace program;

void TrainAndTestProgram::run()
{
    for( auto it_topology = topologyVec_.begin(); it_topology != topologyVec_.end(); ++it_topology )
    {
        for( auto it_epoch = epochVec_.begin(); it_epoch != epochVec_.end(); ++it_epoch )
        {
            for( auto it_batch_size = batchSizeVec_.begin(); it_batch_size != batchSizeVec_.end(); ++it_batch_size )
            {
                for( auto it_function = functionVec_.begin(); it_function != functionVec_.end(); ++it_function )
                {
                    for( auto it_eta = etaVec_.begin(); it_eta != etaVec_.end(); ++it_eta )
                    {
                        //TODO  train
                    }
                }
            }
        }
    }

    //TODO test
}

TrainAndTestProgram::TrainAndTestProgram( std::vector< std::shared_ptr< house::NormalizedValuesHouse > > &training_data,
                                          std::vector< int > &epoch_vec,
                                          std::vector< int > &batch_size_vec,
                                          std::vector< neural_network::functions::ActivationFunctions_E > &function_vec,
                                          std::vector< double > &eta_vec,
                                          std::vector <neural_network::Topology_E > &topology_vec,
                                          int tolerance )

        : trainingData_( std::move( training_data ) ),
          epochVec_( std::move( epoch_vec ) ),
          batchSizeVec_( std::move( batch_size_vec ) ),
          functionVec_( std::move( function_vec ) ),
          etaVec_( std::move( eta_vec ) ),
          topologyVec_( std::move( topology_vec ) ),
          tolerance_( tolerance )
{

}

TrainAndTestProgram::~TrainAndTestProgram()
{
    Serializator::getInstance().closeLoggerFile();
}

