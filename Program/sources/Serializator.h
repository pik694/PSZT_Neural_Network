//
// Created by Marcin Dziedzic on 08/01/2018.
//

#ifndef PSZT_NEURAL_NETWORK_SERIALIZATOR_H
#define PSZT_NEURAL_NETWORK_SERIALIZATOR_H

#include <fstream>
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <string>
#include "neural_network/NeuralNetwork.h"

template<typename T>
class Serializator {

public:
	static Serializator &getInstance() { // TODO change into a ptr
		static Serializator instance;
		return instance;
	}

	void setOutputDirectory(const std::string &directory) {
		outputDirectory_ = directory;
	}

	void setLoggerFile(std::ofstream &loggerStream) {

		loggerFile_ = std::move(loggerStream);

	}

	void closeLoggerFile() {
		if (loggerFile_.is_open())
			loggerFile_.close();
	}

	void
	serialize(neural_network::NeuralNetwork<T> &neuralNetwork, neural_network::functions::ActivationFunctions_E function,
	          int epochs, int batchSize, double eta, int testsPct, double MSE) {

		if (outputDirectory_.length() == 0) {
			std::cerr << "Did not set output directory. Output directory was set to /tmp/neural_net/" << std::endl;
			outputDirectory_ = "/tmp/neural_net/";
		}

		std::string fileName = outputDirectory_ + getCurrentDateTime() + "_" + std::to_string(id_++) + ".nnet";

		std::ofstream currentNet(fileName);

		if (!currentNet.is_open()) {
			throw std::runtime_error("Could not open file : " + fileName);
		}

		serializeNeuralNetwork(currentNet, neuralNetwork, function, epochs, batchSize, eta, testsPct, MSE);

		currentNet.close();

		saveNetToLogger(neuralNetwork, function, epochs, batchSize, eta, testsPct, MSE);
	}

	neural_network::NeuralNetwork<T> deserialize(std::ifstream &file) {
		return neural_network::NeuralNetwork<T>(std::vector<int>(),
		                                        neural_network::functions::ActivationFunctions_E::step);
	}

	virtual ~Serializator() = default;

private:
	Serializator():id_(0){}

	std::ofstream loggerFile_;
	std::string outputDirectory_;

	std::string getCurrentDateTime() {

		auto now = std::chrono::system_clock::now();
		std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
		return std::to_string(ms.count());
	}

	void serializeNeuralNetwork(std::ofstream &stream, neural_network::NeuralNetwork<T> &net,
	                            neural_network::functions::ActivationFunctions_E func,
	                            int epochs, int batchSize, double eta, int testPct, double MSE) {



		stream << "epochs,batch size,eta,tests %,activation function,net topology,MSE" << std::endl;

		writeNetInfo(stream, net, func, epochs, batchSize, eta, testPct, MSE);

		writeWeights(stream, net);

	}

	void saveNetToLogger(neural_network::NeuralNetwork<T> &net,
	                     neural_network::functions::ActivationFunctions_E func,
	                     int epochs, int batchSize, double eta, int testPct, double MSE) {

		if (!loggerFile_.is_open()) {
			std::cerr << "Broken logger file : stream is closed. Omitted saving net to logger." << std::endl;
			return;
		}


		writeNetInfo(loggerFile_, net, func, epochs, batchSize, eta, testPct, MSE);

	}

	void writeWeights(std::ofstream &stream, neural_network::NeuralNetwork<T> &net) {

		auto weights = net.getWeights();

		for (auto &layer : weights) {
			stream << std::endl;
			for (auto &inputNeuron : layer) {
				for (auto &weight : inputNeuron) {
					stream << weight << ",";
				}
				stream << std::endl;
			}
		}

	}

	void writeNetInfo(std::ofstream &stream, neural_network::NeuralNetwork<T> &net,
	                  neural_network::functions::ActivationFunctions_E func,
	                  int epochs, int batchSize, double eta, int testPct, double MSE) {


		auto topology = net.getTopology();

		stream << epochs << ",";
		stream << batchSize << ",";
		stream << eta << ",";
		stream << testPct << ",";
		stream << static_cast<int>(func) << ",";
		std::copy(topology.begin(), topology.end(),
		          std::ostream_iterator<int>(stream, ";"));
		stream << "," << MSE << std::endl;

	}

	int id_;

};


#endif //PSZT_NEURAL_NETWORK_SERIALIZATOR_H
