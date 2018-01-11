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

    loggerStream = std::move(loggerStream);

}

void Serializator::closeLoggerFile() {
    if (loggerFile.is_open())
        loggerFile.close();
}

void Serializator::setOutputDirectory(const std::string& directory) {
    outputDirectory = directory;
}


void
Serializator::serialize(neural_network::NeuralNetwork &neuralNetwork, neural_network::functions::ActivationFunctions_E function,
                        int epochs, int batchSize, double eta, int testsPct, double MSE) {

    if (outputDirectory.length() == 0){
        std::cerr << "Did not set output directory. Output directory was set to /tmp/neural_net/" << std::endl;
        outputDirectory = "/tmp/neural_net/";
    }

    std::string fileName =  outputDirectory + getCurrentDateTime() + ".nnet";

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

	if (!loggerFile.is_open()){
		std::cerr << "Broken logger file : stream is closed. Omitted saving net to logger." << std:: endl;
		return;
	}


	writeNetInfo(loggerFile, net, func, epochs, batchSize, eta, testPct, MSE);

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








//neural_network::NeuralNetwork Serializator::deserialize(std::ifstream &file) {
//
//    neural_network::functions::ActivationFunctions_E activationFunction = readActivationFunction(file);
//    std::vector<int> topology = readTopology(file);
//    neural_network::NeuralNetwork::weights_t weights = readWeights(file, topology);
//    return neural_network::NeuralNetwork(weights, activationFunction);
//}
//
//void Serializator::writeActivationFunction(std::ofstream &file) {
//    // przydalby sie  getter do funkcji
//    // todo
//    file << "2\n";
//}
//
//void Serializator::writeTopology(std::ofstream &file, neural_network::NeuralNetwork &neuralNetwork) {
//    for (int node : neuralNetwork.getTopology()) {
//        file << node;
//        file << ",";
//    }
//    file << "\n";
//}
//
//void Serializator::writeWeights(std::ofstream &file, neural_network::NeuralNetwork &neuralNetwork) {
//    //layers
//    for (std::vector<std::vector<double>> layer : neuralNetwork.getWeights()) {
//        //nodes
//        for (std::vector<double> node : layer) {
//            //walue
//            for (double value : node) {
//                file << value;
//                file << ",";
//            }
//        }
//    }
//
//}
//
//neural_network::functions::ActivationFunctions_E Serializator::readActivationFunction(std::ifstream &file) {
//    std::string sample;
//
//    getline(file, sample);
//    int functionNumber = stoi(sample);
//    neural_network::functions::ActivationFunctions_E activationFunctions_e;
//    switch (functionNumber) {
//
//        case 1:
//            activationFunctions_e = neural_network::functions::ActivationFunctions_E::step;
//            break;
//        case 2:
//            activationFunctions_e = neural_network::functions::ActivationFunctions_E::fastSigmoid;
//            break;
//        case 3:
//            activationFunctions_e = neural_network::functions::ActivationFunctions_E::logistic;
//            break;
//        case 4:
//            activationFunctions_e = neural_network::functions::ActivationFunctions_E::hyperbolicTangent;
//            break;
//        case 5:
//            activationFunctions_e = neural_network::functions::ActivationFunctions_E::specificAlgebraic;
//            break;
//        default:
//            activationFunctions_e = neural_network::functions::ActivationFunctions_E::fastSigmoid;
//    }
//    return activationFunctions_e;
//}
//
//std::vector<int> Serializator::readTopology(std::ifstream &file) {
//    std::string sample;
//    std::vector<int> topology;
//
//    getline(file, sample, ',');
//    topology.push_back(stoi(sample));
//    while (file.good()) {
//
//        if (sample.find('\n') != std::string::npos) {
//            //output layer
//            topology.push_back(stoi(sample));
//            break;
//            //std::cout << "new line!";
//        }
//
//        //std::cout << sample;
//        //inner topology
//        topology.push_back(stoi(sample));
//    }
//    return topology;
//}
//
//neural_network::NeuralNetwork::weights_t Serializator::readWeights(std::ifstream &file, std::vector<int> &topology) {
//    std::string sample;
//    neural_network::NeuralNetwork::weights_t weights;
//
//    weights.resize(topology.size());
//    for (auto i = 0; i < topology.size(); i++) {
//        weights.at(i).resize(topology.at(i));
//        for (auto j = 0; j < topology.at(i); j++) {
//            weights.at(i).at(j).resize((topology.at(i + 1)));
//            for (auto k = 0; k < topology.at(i + 1); ++k) {
//                getline(file, sample, ',');
//                weights[i][j][k] = stoi(sample);
//            }
//        }
//    }
//    return weights;
//}
//
//void Serializator::setOuptutDirectory(const std::string &) {
//    // TODO
//}
//
//void Serializator::setLoggerFile(std::ofstream&) {
//    // TODO
//}
//
//void Serializator::closeLoggerFile() {
//    // TODO
//}
//
//void
//Serializator::serialize(neural_network::NeuralNetwork &neuralNetwork, neural_network::functions::ActivationFunctions_E,
//                        int epochs, int batchSize, double eta, int testsPct, double MSE) {
//
//}
//
///*void Serializator::saveResults(neural_network::NeuralNetwork &neuralNetwork, std::string &fileName) {
//    std::ofstream file;
//    file.open(fileName);
//    //todo
//}*/
//
//
//
//
//
