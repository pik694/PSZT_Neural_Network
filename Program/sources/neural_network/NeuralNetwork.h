//Created by Daniel Bigos

#include <vector>
#include "TrainingDataFactory.h"
#include "FileReader.h"

#include "neural_network/neurons/Neuron.h"
#include "house/NormalizedValuesHouse.h"


namespace neural_network {
	class NeuralNetwork {
	public:
		NeuralNetwork(std::vector<int> neuronsInLayer,
		              std::function<double(double)>  function,
		              std::function<double(double)> derivative );

		double calculatePrice(const  NormalizedValuesHouse& house) {return feedForward(house);}

		void propagateBack(const  NormalizedValuesHouse&);

		double feedForward(const  NormalizedValuesHouse&);

		virtual ~NeuralNetwork() = default;

	private:

		using layer_t = std::vector<std::shared_ptr<neurons::Neuron>>;


		void setInputs(const  NormalizedValuesHouse&);
		double getNetResult();

		std::vector<layer_t> neurons_;

	};
}
