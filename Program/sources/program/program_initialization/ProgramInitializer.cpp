//
// Created by Piotr Żelazko on 05.01.2018.
//

#include <iostream>
#include "ProgramInitializer.h"


using namespace program::program_initializer;
using namespace boost::program_options;

ProgramInitializer::ProgramInitializer(int argc, const char **argv) :
		argc_(argc),
		argv_(argv),
		description_("Allowed options"),
		variablesMap_() {


	description_.add_options()
			(command(HELP, "h").c_str(), "Show this help message")
			(command(VERSION, "v").c_str(), "Show program version")
			(command(FILE_IN, "i").c_str(), value<std::string>(&inputFileName)->required(), "Specifies input file");

}

std::string ProgramInitializer::command(std::string longCommand, std::string shortCommand) const {
	return (longCommand + "," + shortCommand);
}

std::shared_ptr<program::Program> ProgramInitializer::getProgram() {

	std::shared_ptr<Program> program;

	try {
		parse();
	}
		//TODO : check whether we should catch a const & to an exception
	catch (const boost::program_options::required_option &e) {
		if (variablesMap_.count(HELP) || variablesMap_.count(VERSION)) {
			//TODO : shared ptrs
			std::shared_ptr<SimpleProgram> program = std::shared_ptr<SimpleProgram>(new SimpleProgram());

			if (variablesMap_.count(HELP)){
				program = std::shared_ptr<SimpleProgram>(new HelpProgram(program, description_));
			}
			if (variablesMap_.count(VERSION)){
				program = std::shared_ptr<SimpleProgram>(new GetVersionProgram(program));
			}

			return program;

		} else throw e;
	}

	return program;
}

void ProgramInitializer::parse() {

	store(parse_command_line(argc_, argv_, description_), variablesMap_);
	notify(variablesMap_);

}


