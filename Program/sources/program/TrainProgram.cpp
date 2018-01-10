#include "TrainProgram.h"

using namespace program;

void TrainProgram::run()
{

    for( auto it_topology = topologyVec_.begin(); it_topology != topologyVec_.end(); ++it_topology )
    {
        for( auto it_epoch = epochVec_.begin(); it_epoch != epochVec_.end(); ++it_epoch )
        {
            for( auto it_pack = packVec_.begin(); it_pack != packVec_.end(); ++it_pack )
            {
                for( auto it_function = functionVec_.begin(); it_function != functionVec_.end(); ++it_function )
                {
                    for( auto it_eta = etaVec_.begin(); it_eta != etaVec_.end(); ++it_eta )

                    {
                        //TODO train
                        //na 1 eta parametr wątków
                        //kazdy watek zwroci inny wynik, za kazdym razem puszczac tak aby bylo zajete maks watków, bez sprawdzenia
                        //kady watek liczy siec
                        //uczenie 1 konstruktor, 2 to testowanie
                        //musze zrobic statyczna funkcje do stochasticGradient....
                        //kazda siec do pliku
                        //refresh w pętli
                    }
                }
            }
        }
    }
}

TrainProgram::TrainProgram( std::vector< std::shared_ptr< house::NormalizedValuesHouse > > &training_data,
                            std::vector< int > &epoch_vec,
                            std::vector< int > &pack_vec,
                            std::vector< neural_network::functions::ActivationFunctions_E > &function_vec,
                            std::vector< double > &eta_vec,
                            std::vector< neural_network::Topology_E > &topology_vec )

        :   trainingData_( std::move( training_data) ),
            epochVec_( std::move( epoch_vec ) ),
            packVec_( std::move( pack_vec ) ),
            functionVec_( std::move( function_vec ) ),
            etaVec_( std::move( eta_vec ) ),
            topologyVec_( std::move( topology_vec ) )
{
}

TrainProgram::~TrainProgram()
{

}

