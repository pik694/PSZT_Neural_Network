#include <iostream>
#include "Program.h"

using namespace program;

void program::ProgramDecorator::run() {
	program_->run();
}

void GetVersionProgram::run() {
	std::cout << "Program version : " << PROGRAM_VERSION_MAJOR << "." << PROGRAM_VERSION_MINOR << std::endl;
	ProgramDecorator::run();
}

void HelpProgram::run() {
	std::cout << description_ << std::endl;
	ProgramDecorator::run();
}

void ErrorInfoProgram::run() {
	std::cerr << errorMessage_ << std::endl;
	ProgramDecorator::run();
}
