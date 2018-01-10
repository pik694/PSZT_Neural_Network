//
// Created by Marcin Dziedzic on 08/01/2018.
//

#ifndef PSZT_NEURAL_NETWORK_SERIALIZATOR_H
#define PSZT_NEURAL_NETWORK_SERIALIZATOR_H


#include "neural_network/NeuralNetwork.h"

class Serializator {

public:
	static Serializator &getInstance() {
		static Serializator instance;
		return instance;
	}

	void setOuptutDirecotry(const std::string&);
	void setLoggerFile(std::ofstream& );
	void closeLoggerFile();

	void serialize(neural_network::NeuralNetwork &neuralNetwork,
	               neural_network::functions::ActivationFunctions_E,
	               int epochs, int batchSize, double eta);

	neural_network::NeuralNetwork deserialize(std::ifstream &file);

	//obsolete: void saveResults(neural_network::NeuralNetwork &neuralNetwork, std::string &fileName);

private:
	Serializator() = default;

	void writeActivationFunction(std::ofstream &file);

	void writeTopology(std::ofstream &file, neural_network::NeuralNetwork &neuralNetwork);

	void writeWeights(std::ofstream &file, neural_network::NeuralNetwork &neuralNetwork);

	neural_network::functions::ActivationFunctions_E readActivationFunction(std::ifstream &file);

	std::vector<int> readTopology(std::ifstream &file);

	neural_network::NeuralNetwork::weights_t readWeights(std::ifstream &file, std::vector<int> &topology);

};


#endif //PSZT_NEURAL_NETWORK_SERIALIZATOR_H
