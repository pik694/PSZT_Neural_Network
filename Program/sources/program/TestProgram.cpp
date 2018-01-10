#include "TestProgram.h"

using namespace program;

void TestProgram::run()
{
    //TODO test
    //zaorac maks watkow z takimi parametrami jak dostane od MD, progres bar
    //calculatePRICE, DOSTAJE WYNIK ZNORMALIZOWANY I SPRAWDZAM TOLERANCJE, SPRAWDZIC ILE WYNIKOW ZALICZYL
    //WYPISAC ILE WYNIKOW ZALICZYL
}

TestProgram::~TestProgram()
{
 if( neuralFile_.is_open() )
     neuralFile_.close();
}

TestProgram::TestProgram( std::vector< std::shared_ptr< house::NormalizedValuesHouse > > &training_data,
                          std::ifstream &neural_file,
                          std::vector< int > &pack_vec,
                          int tolerance )

        : trainingData_( std::move( training_data ) ),
          neuralFile_( std::move( neural_file ) ),
          tolerance_( tolerance )
{

}

