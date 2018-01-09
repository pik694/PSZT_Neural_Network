// Created by Daniel Bigos

#ifndef PSZT_NEURAL_NETWORK_TRAINANDTESTPROGRAM_H
#define PSZT_NEURAL_NETWORK_TRAINANDTESTPROGRAM_H

#include "Program.h"

namespace program
{
    class TrainAndTestProgram : public Program
    {
    public:
        void run() override;

        ~TrainAndTestProgram() override = default;
    };
}

#endif //PSZT_NEURAL_NETWORK_TRAINANDTESTPROGRAM_H
