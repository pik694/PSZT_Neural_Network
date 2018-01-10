//
// Created by Piotr Żelazko on 05.01.2018.
//

#ifndef PSZT_NEURAL_NETWORK_PROGRAMINITIALIZER_H
#define PSZT_NEURAL_NETWORK_PROGRAMINITIALIZER_H

#include <boost/program_options.hpp>
#include <string>
#include "program/Program.h"
#include "program/TestProgram.h"
#include "program/TrainProgram.h"
#include "program/TrainAndTestProgram.h"
#include "neural_network/ActivationFunctionsBank.h"
#include "neural_network/NeuralNetworkTopology.h"

namespace program {
	namespace program_initializer {

		class ProgramInitializer {
			using c_str = const std::string;

		public:

			ProgramInitializer(int argc, const char **argv);

			std::unique_ptr<Program> getProgram();

			virtual ~ProgramInitializer() = default;

		private:

			void parse();

			std::string command(std::string longCommand, std::string shortCommand) const;

			boost::program_options::options_description infoOptions_;
			boost::program_options::options_description runOptions_;
			boost::program_options::variables_map variablesMap_;
			boost::program_options::positional_options_description positionalOptions_;

			int argc_;
			const char **argv_;

            std::vector< int > epoch_v;
            std::vector< int > batchSize_v;
            std::vector< neural_network::Topology_E > topology_v;
            std::vector< neural_network::functions::ActivationFunctions_E > function_v;
            std::vector< double > eta_v;
            int percentage_;
            std::string neuralNetFile_;
			std::string inputFileName_;
			ExecutionMode_E executionMode_;
			std::string resultPath_;
			std::string loggerFile_;


			c_str HELP = "help";
			c_str VERSION = "version";
			c_str MODE = "mode";
			c_str DATA = "input data";
            c_str PACK = "pack";
            c_str FUNCTION = "function";
            c_str ETA = "eta";
            c_str EPOCH = "epoch";
            c_str TOPOLOGY = "topology";
            c_str TOLERANCE = "tolerance";
            c_str NEURAL_NET = "neural net";
			c_str LOGGER = "logger";
			c_str RESULT = "result path";
		};
	}
}


#endif //PSZT_NEURAL_NETWORK_PROGRAMINITIALIZER_H
