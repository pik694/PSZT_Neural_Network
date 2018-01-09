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

			std::string inputFileName_;
			ExecutionMode_E executionMode_;

			int argc_;
			const char **argv_;

			c_str HELP = "help";
			c_str VERSION = "version";
			c_str MODE = "mode";
			c_str DATA = "input data";
		};
	}
}


#endif //PSZT_NEURAL_NETWORK_PROGRAMINITIALIZER_H
