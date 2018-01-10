#include "TestProgram.h"

using namespace program;

void TestProgram::run()
{
    //TODO test
}

TestProgram::~TestProgram()
{

}

TestProgram::TestProgram( std::vector< std::shared_ptr< house::NormalizedValuesHouse > > *training_data,
                          std::ifstream *neural_file, std::vector< int > *pack_vec, std::vector< int > *tolerance_vec )
{
    trainingData_ = std::move( *training_data );
    neuralFile_ = std::move( *neural_file );
    packVec_ = std::move( *pack_vec );
    toleranceVec_ = std::move( *tolerance_vec );
}

