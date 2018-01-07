//Created by Daniel Bigos

#include <vector>
#include "TrainingDataFactory.h"
#include "FileReader.h"

#include "neural_network/neurons/Neuron.h"


namespace neural_network {
	class NeuralNetwork {
	public:
		NeuralNetwork(std::vector<int> neuronsInLayer,
		              std::function<double(double)>  function,
		              std::function<double(double)> derivative );

		double calculatePrice(const House&) const;

		void propagateBack();

		double feedForward(const House&) const;

		virtual ~NeuralNetwork() = default;

	private:

		using layer_t = std::vector<std::shared_ptr<neurons::Neuron>>;

		std::vector<layer_t> neurons_;

	};
}
