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
        TestProgram( std::vector< std::shared_ptr< house::NormalizedValuesHouse > > &training_data,
                     std::ifstream &neural_file,
                     int tolerance );

        void run() override;

        ~TestProgram() override;
    private:
        std::vector< std::shared_ptr< house::NormalizedValuesHouse > > trainingData_;
        std::ifstream neuralFile_;
        int tolerance_;
    };
}
#endif //PSZT_NEURAL_NETWORK_TESTPROGRAM_H
