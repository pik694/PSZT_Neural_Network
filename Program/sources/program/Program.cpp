#include <iostream>
#include <unistd.h>
#include "Program.h"
#include "progress/ProgressStatusManager.h"

using namespace program;

bool Program::canRefresh_ = true;

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

void Program::refresh()
{
	while( canRefresh_ )
	{
		sleep( SLEEP_TIME );
		progress::ProgressStatusManager::getInstance()->refresh();

	}


}
