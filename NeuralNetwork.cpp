#include "NeuralNetwork.h"

NeuralNetwork::NeuralNetwork()
{
}

void NeuralNetwork::trainOnFile( std::string file_name, const char* separator )
{
	std::vector< std::string > file_data = fileReader_.getFileRows( file_name );
	std::vector< std::shared_ptr< House > > training_data( file_data.size() );
	trainingDataFactory_.run( &file_data , separator, &training_data );
	
	//TODO
	//...
	//...
	//...
}

NeuralNetwork::~NeuralNetwork()
{
}
