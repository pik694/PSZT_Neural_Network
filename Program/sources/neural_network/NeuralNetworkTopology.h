//
// Created by Piotr Żelazko on 09.01.2018.
//

#ifndef PSZT_NEURAL_NETWORK_NEURALNETWORKTOPOLOGY_H
#define PSZT_NEURAL_NETWORK_NEURALNETWORKTOPOLOGY_H

#include <vector>

namespace neural_network{
	enum class Topology_E
	{
		JakaKolwiek = 69
	};

	class TopologyBank{
	public:
		static std::vector<int> getTopology(Topology_E topology);
	};

}

#endif //PSZT_NEURAL_NETWORK_NEURALNETWORKTOPOLOGY_H
