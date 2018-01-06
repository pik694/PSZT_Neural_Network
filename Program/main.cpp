#include "neural_network/NeuralNetwork.h"

#include <program/program_initialization/ProgramInitializer.h>

using namespace neural_network;
using namespace program;


int main(int argc, const char **argv) {

	program_initializer::ProgramInitializer programInitializer (argc, argv);

	auto program = programInitializer.getProgram();

	program->run();

	return 0;
}

