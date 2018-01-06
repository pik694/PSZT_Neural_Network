//
// Created by Piotr Żelazko on 05.01.2018.
//

#ifndef PSZT_NEURAL_NETWORK_PROGRAMINITIALIZER_H
#define PSZT_NEURAL_NETWORK_PROGRAMINITIALIZER_H

#include <boost/program_options.hpp>
#include <string>
#include "program/Program.h"


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

			std::string inputFileName;

			int argc_;
			const char **argv_;

			c_str HELP = "help";
			c_str VERSION = "version";
			c_str FILE_IN = "file";
		};
	}
}


#endif //PSZT_NEURAL_NETWORK_PROGRAMINITIALIZER_H
