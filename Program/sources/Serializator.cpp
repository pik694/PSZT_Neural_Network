////
//// Created by Marcin Dziedzic on 08/01/2018.
////
//
#include <fstream>
#include <chrono>  // chrono::system_clock
#include <ctime>   // localtime
#include <sstream> // stringstream
#include <iomanip> // put_time
#include <string>  // string
#include "Serializator.h"


void Serializator::setLoggerFile(std::ofstream& loggerStream) { // TODO: make sure it that the stream overwrites file

    loggerFile_ = std::move(loggerStream);

}

void Serializator::closeLoggerFile() {
    if (loggerFile_.is_open())
        loggerFile_.close();
}

void Serializator::setOutputDirectory(const std::string& directory) {
    outputDirectory_ = directory;
}


void
Serializator::serialize(neural_network::NeuralNetwork &neuralNetwork, neural_network::functions::ActivationFunctions_E function,
                        int epochs, int batchSize, double eta, int testsPct, double MSE) {

    if (outputDirectory_.length() == 0){
        std::cerr << "Did not set output directory. Output directory was set to /tmp/neural_net/" << std::endl;
        outputDirectory_ = "/tmp/neural_net/";
    }

    std::string fileName =  outputDirectory_ + getCurrentDateTime() + ".nnet";

    std::ofstream currentNet (fileName);

    if (!currentNet.is_open()){
        throw std::runtime_error("Could not open file : " + fileName);
    }

	serializeNeuralNetwork(currentNet, neuralNetwork,function, epochs, batchSize, eta, testsPct, MSE);

    currentNet.close();

	saveNetToLogger(neuralNetwork,function, epochs, batchSize, eta, testsPct, MSE);
}

void Serializator::serializeNeuralNetwork(std::ofstream &stream, neural_network::NeuralNetwork &net,
                                          neural_network::functions::ActivationFunctions_E func,
                                          int epochs, int batchSize, double eta, int testPct, double MSE) {



	stream << "epochs,batch size,eta,tests %,activation function,net topology,MSE" << std::endl;

	writeNetInfo(stream, net, func, epochs, batchSize, eta, testPct, MSE);

	writeWeights(stream, net);

}



void
Serializator::saveNetToLogger(neural_network::NeuralNetwork &net, neural_network::functions::ActivationFunctions_E func,
                              int epochs, int batchSize, double eta, int testPct, double MSE) {

	if (!loggerFile_.is_open()){
		std::cerr << "Broken logger file : stream is closed. Omitted saving net to logger." << std:: endl;
		return;
	}


	writeNetInfo(loggerFile_, net, func, epochs, batchSize, eta, testPct, MSE);

}

void Serializator::writeNetInfo(std::ofstream &stream, neural_network::NeuralNetwork &net,
                                neural_network::functions::ActivationFunctions_E func, int epochs, int batchSize,
                                double eta, int testPct, double MSE) {


	auto topology = net.getTopology();

	stream << epochs << ",";
	stream << batchSize << ",";
	stream << eta << ",";
	stream << testPct << ",";
	stream <<  static_cast<int>(func) << ",";
	std::copy(topology.begin(), topology.end(),
	          std::ostream_iterator<int>(stream, ";"));
	stream << "," << MSE << std::endl;

}


std::string Serializator::getCurrentDateTime()
{

	auto now = std::chrono::system_clock::now();
	std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
	return std::to_string(ms.count());
}

void Serializator::writeWeights(std::ofstream &stream, neural_network::NeuralNetwork &net) {

	auto weights = net.getWeights();

	for (auto& layer : weights){
		stream << std::endl;
		for (auto& inputNeuron : layer){
			for(auto& weight : inputNeuron){
				stream << weight << ",";
			}
			stream << std::endl;
		}
	}

}

neural_network::NeuralNetwork Serializator::deserialize(std::ifstream &file) {
	return neural_network::NeuralNetwork(std::vector<int>(), neural_network::functions::ActivationFunctions_E::step );
}
