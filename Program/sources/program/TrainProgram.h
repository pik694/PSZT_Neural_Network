// Created by Daniel Bigos

#ifndef PSZT_NEURAL_NETWORK_TRAINPROGRAM_H
#define PSZT_NEURAL_NETWORK_TRAINPROGRAM_H

#include "Program.h"

namespace program
{
    class TrainProgram : public Program
    {
    public:
        void run() override;
        virtual ~TrainProgram() = default;
    private:
        /*std::vector< std::shared_ptr< NormalizedHouse> > training_data;
        std::vector< >*/
    };
}

#endif //PSZT_NEURAL_NETWORK_TRAINPROGRAM_H
