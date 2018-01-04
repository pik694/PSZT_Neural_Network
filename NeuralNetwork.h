//Created by Daniel Bigos

#include <vector>
#include "TrainingDataFactory.h"
#include "FileReader.h"

class NeuralNetwork
{
private:
	std::vector< std::string > fileRows_;
	FileReader fileReader_;
	TrainingDataFactory trainingDataFactory_;
public:
	NeuralNetwork();
	void trainOnFile( std::string file_name, const char* separator );
	~NeuralNetwork();
};

