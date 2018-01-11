//
// Created by Marcin Dziedzic on 08/01/2018.
//

#ifndef PSZT_NEURAL_NETWORK_SERIALIZATOR_H
#define PSZT_NEURAL_NETWORK_SERIALIZATOR_H

#include <fstream>
#include "neural_network/NeuralNetwork.h"

class Serializator {

public:
	static Serializator &getInstance() { // TODO change into a ptr
		static Serializator instance;
		return instance;
	}

	void setOutputDirectory(const std::string &);
	void setLoggerFile(std::ofstream& );
	void closeLoggerFile();

	void serialize(neural_network::NeuralNetwork &neuralNetwork, neural_network::functions::ActivationFunctions_E,
	               int epochs, int batchSize, double eta, int testsPct, double MSE);

	neural_network::NeuralNetwork deserialize(std::ifstream &file);

	virtual ~Serializator() = default;

private:
	Serializator() = default;

	std::ofstream loggerFile_;
	std::string outputDirectory_;

	std::string getCurrentDateTime();

	void serializeNeuralNetwork(std::ofstream &stream, neural_network::NeuralNetwork &net,
	                            neural_network::functions::ActivationFunctions_E func,
	                            int epochs, int batchSize, double eta, int testPct, double MSE);

	void saveNetToLogger(neural_network::NeuralNetwork &net,
	                     neural_network::functions::ActivationFunctions_E func,
	                     int epochs, int batchSize, double eta, int testPct, double MSE);

	void writeWeights(std::ofstream &stream, neural_network::NeuralNetwork &net);

	void writeNetInfo(std::ofstream& stream, neural_network::NeuralNetwork &net,
	                  neural_network::functions::ActivationFunctions_E func,
	                  int epochs, int batchSize, double eta, int testPct, double MSE);

//	void writeActivationFunction(std::ofstream &file);
//
//	void writeTopology(std::ofstream &file, neural_network::NeuralNetwork &neuralNetwork);
//
//	void writeWeights(std::ofstream &file, neural_network::NeuralNetwork &neuralNetwork);
//
//	neural_network::functions::ActivationFunctions_E readActivationFunction(std::ifstream &file);
//
//	std::vector<int> readTopology(std::ifstream &file);
//
//	neural_network::NeuralNetwork::weights_t readWeights(std::ifstream &file, std::vector<int> &topology);

};


#endif //PSZT_NEURAL_NETWORK_SERIALIZATOR_H
