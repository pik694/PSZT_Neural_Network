//
// Created by Marcin Dziedzic on 08/01/2018.
//

#include <fstream>
#include "Serializator.h"

/*void Serializator::serialize(neural_network::NeuralNetwork &neuralNetwork, std::string &fileName) {
    std::ofstream file;
    file.open(fileName);
    writeActivationFunction(file);
    writeTopology(file, neuralNetwork);
    writeWeights(file, neuralNetwork);
    file.close();
}*/

neural_network::NeuralNetwork Serializator::deserialize(std::ifstream &file) {

    neural_network::functions::ActivationFunctions_E activationFunction = readActivationFunction(file);
    std::vector<int> topology = readTopology(file);
    neural_network::NeuralNetwork::weights_t weights = readWeights(file, topology);
    return neural_network::NeuralNetwork(weights, activationFunction);
}

void Serializator::writeActivationFunction(std::ofstream &file) {
    // przydalby sie  getter do funkcji
    // todo
    file << "2\n";
}

void Serializator::writeTopology(std::ofstream &file, neural_network::NeuralNetwork &neuralNetwork) {
    for (int node : neuralNetwork.getTopology()) {
        file << node;
        file << ",";
    }
    file << "\n";
}

void Serializator::writeWeights(std::ofstream &file, neural_network::NeuralNetwork &neuralNetwork) {
    //layers
    for (std::vector<std::vector<double>> layer : neuralNetwork.getWeights()) {
        //nodes
        for (std::vector<double> node : layer) {
            //walue
            for (double value : node) {
                file << value;
                file << ",";
            }
        }
    }

}

neural_network::functions::ActivationFunctions_E Serializator::readActivationFunction(std::ifstream &file) {
    std::string sample;

    getline(file, sample);
    int functionNumber = stoi(sample);
    neural_network::functions::ActivationFunctions_E activationFunctions_e;
    switch (functionNumber) {

        case 1:
            activationFunctions_e = neural_network::functions::ActivationFunctions_E::step;
            break;
        case 2:
            activationFunctions_e = neural_network::functions::ActivationFunctions_E::fastSigmoid;
            break;
        case 3:
            activationFunctions_e = neural_network::functions::ActivationFunctions_E::logistic;
            break;
        case 4:
            activationFunctions_e = neural_network::functions::ActivationFunctions_E::hyperbolicTangent;
            break;
        case 5:
            activationFunctions_e = neural_network::functions::ActivationFunctions_E::specificAlgebraic;
            break;
        default:
            activationFunctions_e = neural_network::functions::ActivationFunctions_E::fastSigmoid;
    }
    return activationFunctions_e;
}

std::vector<int> Serializator::readTopology(std::ifstream &file) {
    std::string sample;
    std::vector<int> topology;

    getline(file, sample, ',');
    topology.push_back(stoi(sample));
    while (file.good()) {

        if (sample.find('\n') != std::string::npos) {
            //output layer
            topology.push_back(stoi(sample));
            break;
            //std::cout << "new line!";
        }

        //std::cout << sample;
        //inner topology
        topology.push_back(stoi(sample));
    }
    return topology;
}

neural_network::NeuralNetwork::weights_t Serializator::readWeights(std::ifstream &file, std::vector<int> &topology) {
    std::string sample;
    neural_network::NeuralNetwork::weights_t weights;

    weights.resize(topology.size());
    for (auto i = 0; i < topology.size(); i++) {
        weights.at(i).resize(topology.at(i));
        for (auto j = 0; j < topology.at(i); j++) {
            weights.at(i).at(j).resize((topology.at(i + 1)));
            for (auto k = 0; k < topology.at(i + 1); ++k) {
                getline(file, sample, ',');
                weights[i][j][k] = stoi(sample);
            }
        }
    }
    return weights;
}

void Serializator::setOuptutDirecotry(const std::string &) {
    // TODO
}

void Serializator::setLoggerFile(std::ofstream) {
    // TODO
}

void Serializator::closeLoggerFile() {
    // TODO
}

void
Serializator::serialize(neural_network::NeuralNetwork &neuralNetwork, neural_network::functions::ActivationFunctions_E,
                        int epochs, int batchSize, double eta) {

}

/*void Serializator::saveResults(neural_network::NeuralNetwork &neuralNetwork, std::string &fileName) {
    std::ofstream file;
    file.open(fileName);
    //todo
}*/





