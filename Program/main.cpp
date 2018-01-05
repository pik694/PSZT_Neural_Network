#include "neural_network/NeuralNetwork.h"

#include <program/program_initialization/ProgramInitializer.h>

using namespace neural_network;

int program::SimpleProgram::ID = 0;

int main( int argc,const char** argv )
{
//	std::string file_name( "kc_house_data.csv" );
//	const char separator = ',';
//	NeuralNetwork neural_network;
//	neural_network.trainOnFile( file_name, &separator );
//


	program::program_initializer::ProgramInitializer a (argc, argv);

	a.getProgram()->run();

	return 0;
}

