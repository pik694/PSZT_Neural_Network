//
// Created by Piotr Żelazko on 09.01.2018.
//

#include <map>
#include "NeuralNetworkTopology.h"

using namespace neural_network;

std::vector<int> TopologyBank::getTopology(Topology_E topology) {
	static const std::map<Topology_E, std::vector<int>> map = {
			{Topology_E::_5_5,      {5,  5}},
			{Topology_E::_10_10,    {10, 10}},
			{Topology_E::_15_5,     {15, 5}},
			{Topology_E::_15_10,    {15, 10}},
			{Topology_E::_20_10,    {20, 10}},
			{Topology_E::_20_20,    {20, 20}},
			{Topology_E::_30_15,    {30, 15}},
			{Topology_E::_5_5_5,    {5,  5,  5}},
			{Topology_E::_500, {500}},
			{Topology_E::_1000, {1000}},
			{Topology_E::_1500, {1500}},
			{Topology_E::_2000, {2000}},

	};

	return map.at(topology);
}
