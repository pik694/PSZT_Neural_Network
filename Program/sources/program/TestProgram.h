// Created by Daniel Bigos

#ifndef PSZT_NEURAL_NETWORK_TESTPROGRAM_H
#define PSZT_NEURAL_NETWORK_TESTPROGRAM_H

#include <fstream>
#include "Program.h"
#include "house/NormalizedValuesHouse.h"

namespace program
{
    class TestProgram : public Program
    {
    public:
        TestProgram( std::vector< std::shared_ptr< house::NormalizedValuesHouse > > *training_data,
                     std::ifstream* neural_file, std::vector< int > *pack_vec,
                     std::vector< int >* tolerance_vec );
        void run() override;

        ~TestProgram() override;
    private:
        std::vector< std::shared_ptr< house::NormalizedValuesHouse > > trainingData_;
        std::ifstream neuralFile_;
        std::vector< int > packVec_;
        std::vector< int > toleranceVec_;
    };
}
#endif //PSZT_NEURAL_NETWORK_TESTPROGRAM_H
