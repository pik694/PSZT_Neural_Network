#include "neural_network/NeuralNetwork.h"

using namespace neural_network;

int main( int argc, char* argv[] )
{
	std::string file_name( "kc_house_data.csv" );
	const char separator = ',';
	NeuralNetwork neural_network;
	neural_network.trainOnFile( file_name, &separator );
	return 0;
}

