#include "TestProgram.h"
#include "neural_network/NeuralNetwork.h"
#include "Serializator.h"
#include "progress/ProgressStatusManager.h"

using namespace program;
using namespace neural_network;
using namespace progress;

void TestProgram::run()
{
    unsigned long tests_passed = 0;
    int progress = 0;
    NeuralNetwork neural_network = Serializator::getInstance().deserialize( neuralFile_ );
    ProgressStatusManager::getInstance()->init( "Neural network testing", trainingData_.size() );
    for( auto it = trainingData_.begin(); it != trainingData_.end(); ++it, ++progress )
    {
        double min_price = (double)( ( 100 - tolerance_ ) / 100 ) * it->get()->getPrice();
        double max_price = (double)( ( 100 + tolerance_ ) / 100 ) * it->get()->getPrice();
        double price = neural_network.calculateHousesPrice( *( it->get() ) );

        if( price >= min_price && price <= max_price )
            ++tests_passed;

        if( progress == PROGRESS_INFO )
        {
            ProgressStatusManager::getInstance()->addProgress( progress );
            ProgressStatusManager::getInstance()->refresh();
            progress = 0;
        }
    }

    ProgressStatusManager::getInstance()->addProgress( progress );
    ProgressStatusManager::getInstance()->deinit();

    std::cout << "Passed: " << tests_passed << " from " << trainingData_.size() << " tests" << std::endl;
}

TestProgram::~TestProgram()
{
 if( neuralFile_.is_open() )
     neuralFile_.close();
}

TestProgram::TestProgram( std::vector< std::shared_ptr< house::NormalizedValuesHouse > > &training_data,
                          std::ifstream &neural_file,
                          int tolerance )

        : trainingData_( std::move( training_data ) ),
          neuralFile_( std::move( neural_file ) ),
          tolerance_( tolerance )
{

}

