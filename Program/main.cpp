#include "neural_network/NeuralNetwork.h"

#include <program/program_initialization/ProgramInitializer.h>

using namespace neural_network;
using namespace program;


int main(int argc, const char **argv) {
//	std::string file_name( "kc_house_data.csv" );
//	const char separator = ',';
//	NeuralNetwork neural_network;
//	neural_network.trainOnFile( file_name, &separator );
//

	program_initializer::ProgramInitializer programInitializer (argc, argv);

	auto program = programInitializer.getProgram();
	program->run();

	return 0;
}

