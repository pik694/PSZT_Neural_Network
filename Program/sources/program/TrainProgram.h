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
    };
}

#endif //PSZT_NEURAL_NETWORK_TRAINPROGRAM_H
