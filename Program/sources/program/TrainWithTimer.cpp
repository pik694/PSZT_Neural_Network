#include "TrainWithTimer.h"

using namespace program;
using namespace neural_network;
using namespace progress;
using NHouse = house::NormalizedValuesHouse;

TrainWithTimer::TrainWithTimer(std::vector<house::NormalizedValuesHouse> &training_data, unsigned time,
                               std::vector<int> &batch_size_vec,
                               std::vector<neural_network::functions::ActivationFunctions_E> &function_vec,
                               std::vector<double> &eta_vec, std::vector<neural_network::Topology_E> &topology_vec,
                               int percentage, int threads_for_eta)
        : trainingData_(std::move(training_data)),
          time_ (time),
          batchSizeVec_(std::move(batch_size_vec)),
          functionVec_(std::move(function_vec)),
          etaVec_(std::move(eta_vec)),
          topologyVec_(std::move(topology_vec)),
          percentage_(percentage),
          threadsForEta_(threads_for_eta),
          iterations_(0)
{

}

void TrainWithTimer::run()
{
    for(auto it_topology = topologyVec_.begin(); it_topology != topologyVec_.end(); ++it_topology) {
        for(auto it_batch_size = batchSizeVec_.begin(); it_batch_size != batchSizeVec_.end(); ++it_batch_size) {
            for(auto it_function = functionVec_.begin(); it_function != functionVec_.end(); ++it_function) {
                for(auto it_eta = etaVec_.begin(); it_eta != etaVec_.end(); ++it_eta) {
                    for(unsigned threads_count = 0; threads_count < threadsForEta_; ++threads_count) {
                            NeuralNetwork<NHouse> neural_network(TopologyBank::getTopology(*it_topology), *it_function);
                            configVec_.emplace_back(neural_network, 1, *it_batch_size, *it_eta, percentage_,
                                                    std::numeric_limits<double>::max(), *it_function, time_);
                        }
                    }
                }
            }
    }

    doTraining();
}

void TrainWithTimer::doTraining()
{
    std::vector<TimerTuple> tmp_vector;

    while (!configVec_.empty()) {

        tmp_vector.clear();
        threadsVec_.clear();

        for (int i = 0; i < THREADS_COUNT && !configVec_.empty(); ++i) {
            tmp_vector.emplace_back(std::move(configVec_.back()));
            configVec_.pop_back();
        }

        setThreads(static_cast<int>(tmp_vector.size()));
        ProgressStatusManager::getInstance()->init("Training neural network", time_ * 66);

        for (auto it = tmp_vector.begin(); it != tmp_vector.end(); ++it)
            threadsVec_.emplace_back(trainNeuralNet, std::ref(*it), std::ref(trainingData_));

        while (getThreads()) {
            ProgressStatusManager::getInstance()->refresh();
            sleep(SLEEP_TIME);
            ProgressStatusManager::getInstance()->addProgress(1);
        }

        for (auto it_t = threadsVec_.begin(); it_t != threadsVec_.end(); ++it_t)
            it_t->join();

        ProgressStatusManager::getInstance()->deinit();

        for (auto it = tmp_vector.begin(); it != tmp_vector.end(); ++it)
            Serializator<house::NormalizedValuesHouse>::getInstance().serialize(std::get<NEURAL_NETWORK>(*it),
                                                                                std::get<ACTIVATION_FUNCTION>(*it),
                                                                                std::get<EPOCHS>(*it),
                                                                                std::get<BATCH_SIZE>(*it),
                                                                                std::get<ETA>(*it),
                                                                                std::get<TEST_PERCENTAGE>(*it),
                                                                                std::get<MSE>(*it));


    }
}


TrainWithTimer::~TrainWithTimer() {

}

void TrainWithTimer::trainNeuralNet(TimerTuple &config, const std::vector<house::NormalizedValuesHouse> &training_data)
{
    auto start = std::chrono::system_clock::now();
    auto duration = std::chrono::minutes( std::get<TIME>(config) );
    while( ( std::chrono::system_clock::now() - start ) < duration)
    {
        std::get<MSE>(config) = std::get<NEURAL_NETWORK>(config).stochasticGradientDescent(training_data, 1,
                                                                                           std::get<BATCH_SIZE>(config),
                                                                                           std::get<ETA>(config),
                                                                                           std::get<TEST_PERCENTAGE>(config),
                                                                                           []{});
        int epochs = std::get<EPOCHS>(config);
        ++epochs;
        std::get<EPOCHS>(config) = epochs;
    }
    decrementThreads();
}
