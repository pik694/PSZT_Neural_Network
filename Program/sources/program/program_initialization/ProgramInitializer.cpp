//
// Created by Piotr Żelazko on 05.01.2018.
//

#include <iostream>
#include "FileReader.h"
#include "TrainingDataFactory.h"
#include "ProgramInitializer.h"
#include "progress/ProgressStatusManager.h"

using namespace program;
using namespace program::program_initializer;
using namespace boost::program_options;

ProgramInitializer::ProgramInitializer(int argc, const char **argv) :
		argc_(argc),
		argv_(argv),
		infoOptions_("Info options"),
		runOptions_ ("Program arguments"),
		variablesMap_() {


	infoOptions_.add_options()
			(command(HELP, "h").c_str(), "Show this help message")
			(command(VERSION, "v").c_str(), "Show program version");
	runOptions_.add_options()
			(command(FILE_IN, "i").c_str(), value<std::string>(&inputFileName)->required(), "Specifies input file");

}

std::string ProgramInitializer::command(std::string longCommand, std::string shortCommand) const {
	return (longCommand + "," + shortCommand);
}

std::unique_ptr<program::Program> ProgramInitializer::getProgram() {

	std::unique_ptr<Program> program = std::make_unique<Program>();
	try {
		parse();
	}
	catch (boost::program_options::required_option &e) {

		if (variablesMap_.count(HELP) || variablesMap_.count(VERSION)) {

			if (variablesMap_.count(HELP)){
				program = std::make_unique<HelpProgram>(std::move(program),
				                                        options_description().add(infoOptions_).add(runOptions_));
			}
			if (variablesMap_.count(VERSION)){
				program = std::make_unique<GetVersionProgram>(std::move(program));
			}

			return program;

		}
		else
			return std::make_unique<ErrorInfoProgram>(e.what(), std::move(program));
	}
	catch (std::exception& e){
		return std::make_unique<ErrorInfoProgram>(e.what(), std::move(program));
	}



	try{
		FileReader fileReader;
		ProgressStatusManager::getInstance()->init( "File reading: " + inputFileName );
		std::vector< std::string > file_data = fileReader.getFileRows( inputFileName );
		ProgressStatusManager::getInstance()->deinit();

		ProgressStatusManager::getInstance()->init( "Creating training data", file_data.size() );
		std::vector< std::shared_ptr< House > > training_data( file_data.size() );
		TrainingDataFactory training_data_factory;
		training_data_factory.run( &file_data , &training_data );
		ProgressStatusManager::getInstance()->deinit();
	}
	catch (std::invalid_argument& e){
		return std::make_unique<ErrorInfoProgram>(e.what(), std::move(program));
	}
	catch (std::runtime_error& e){
		return std::make_unique<ErrorInfoProgram>(e.what(), std::move(program));
	}
	catch (std::bad_alloc& e){
		return std::make_unique<ErrorInfoProgram>(e.what(), std::move(program));
	}

	return program;
}

void ProgramInitializer::parse() {

	options_description all;
	all.add(infoOptions_);
	all.add(runOptions_);

	store(parse_command_line(argc_, argv_, all), variablesMap_);

	notify(variablesMap_);
}


