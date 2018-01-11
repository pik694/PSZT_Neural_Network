#include "TrainProgram.h"
#include "progress/ProgressStatusManager.h"
#include "neural_network/NeuralNetworkTopology.h"

using namespace program;
using namespace neural_network;
using namespace progress;

void TrainProgram::run()
{
    refresher_ = std::thread( refresh );

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
                        if( configVec_.size() < THREADS_COUNT )
                        {
                            iterations_ += threadsForEta_ * *it_epoch;
                            for( unsigned threads_count = 0; threads_count < threadsForEta_; ++threads_count )
                            {
                                NeuralNetwork neural_network( TopologyBank::getTopology( *it_topology ), *it_function  );
                                configVec_.emplace_back( neural_network, *it_epoch, *it_batch_size, *it_eta, percentage_, std::numeric_limits< double >::max(), *it_function );
                            }
                        }
                        else
                        {
                            doTraining();
                        }
                    }
                }
            }
        }
    }

    doTraining();
}

TrainProgram::TrainProgram( std::vector< std::shared_ptr< house::NormalizedValuesHouse > > &training_data,
                            std::vector< int > &epoch_vec,
                            std::vector< int > &batch_size_vec,
                            std::vector< neural_network::functions::ActivationFunctions_E > &function_vec,
                            std::vector< double > &eta_vec,
                            std::vector< neural_network::Topology_E > &topology_vec,
                            int percentage,
                            int threads_for_eta )

        :   trainingData_( std::move( training_data) ),
            epochVec_( std::move( epoch_vec ) ),
            batchSizeVec_( std::move( batch_size_vec ) ),
            functionVec_( std::move( function_vec ) ),
            etaVec_( std::move( eta_vec ) ),
            topologyVec_( std::move( topology_vec ) ),
            percentage_( percentage ),
            threadsForEta_( threads_for_eta ),
            iterations_( 0 )
{
}

TrainProgram::~TrainProgram()
{
    Program::canRefresh_ = false;
    Serializator::getInstance().closeLoggerFile();
    refresher_.join();
}

void TrainProgram::trainNeuralNet( ConfigTuple &config,
                                   const std::vector< std::shared_ptr< house::NormalizedValuesHouse > > &training_data)
{
    std::get< MSE >( config ) = std::get< NEURAL_NETWORK >( config ).stochasticGradientDescent( training_data,
                                                                                                  std::get< EPOCHS >( config ),
                                                                                                  std::get< BATCH_SIZE >( config),
                                                                                                  std::get< ETA >( config ), std::get< TEST_PERCENTAGE >( config ) );
}

void TrainProgram::doTraining()
{
    ProgressStatusManager::getInstance()->init( "Training neural network", iterations_ );
    for( auto it = configVec_.begin(); it != configVec_.end(); ++ it )
        threadsVec_.emplace_back( trainNeuralNet, std::ref(*it), std::ref(trainingData_) );


    for( auto it_t = threadsVec_.begin(); it_t != threadsVec_.end(); ++it_t )
        it_t->join();

    ProgressStatusManager::getInstance()->deinit();

    for( auto it = configVec_.begin(); it != configVec_.end(); ++ it )
        Serializator::getInstance().serialize( std::get< NEURAL_NETWORK >( *it ),
                                               std::get< ACTIVATION_FUNCTION >( *it ),
                                               std::get< EPOCHS >( *it ),
                                               std::get< BATCH_SIZE >( *it ),
                                               std::get< ETA >( *it ),
                                               std::get< TEST_PERCENTAGE >( *it ),
                                               std::get< MSE >( *it ) );

    iterations_ = 0;
}

