// Created by Daniel Bigos

#ifndef PSZT_NEURAL_NETWORK_TESTPROGRAM_H
#define PSZT_NEURAL_NETWORK_TESTPROGRAM_H

#include "Program.h"

namespace program
{
    class TestProgram : public Program
    {
    public:
        void run() override;

        ~TestProgram() override = default;
    };
}
#endif //PSZT_NEURAL_NETWORK_TESTPROGRAM_H
