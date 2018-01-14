//
// Created by Piotr Żelazko on 09.01.2018.
//

#ifndef PSZT_NEURAL_NETWORK_NEURALNETWORKTOPOLOGY_H
#define PSZT_NEURAL_NETWORK_NEURALNETWORKTOPOLOGY_H

#include <vector>

namespace neural_network{
	enum class Topology_E
	{
		_5_5,
		_10_10,
		_15_5,
		_15_10,
		_20_10,
		_20_20,
		_30_15,
		_5_5_5,
		_10_10_10,
		_500,
		_1000,
		_1500,
		_2000,
	};

	class TopologyBank{
	public:
		static std::vector<int> getTopology(Topology_E topology);
	};

}

#endif //PSZT_NEURAL_NETWORK_NEURALNETWORKTOPOLOGY_H
