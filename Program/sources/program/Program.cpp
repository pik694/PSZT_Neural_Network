#include <iostream>
#include <unistd.h>
#include "Program.h"
#include "progress/ProgressStatusManager.h"

using namespace program;

int Program::threads_ = 0;
std::mutex Program::mutex_;

void Program::decrementThreads()
{
	std::lock_guard< std::mutex > guard( mutex_ );
	--threads_;
}

int Program::getThreads()
{
	std::lock_guard< std::mutex > guard( mutex_ );
	return threads_;
}

void Program::setThreads( int count )
{
	std::lock_guard< std::mutex > guard( mutex_ );
	threads_ = count;
}

void program::ProgramDecorator::run() {
	program_->run();
}

void GetVersionProgram::run() {
	std::cout << "Program version : " << PROGRAM_VERSION_MAJOR << "." << PROGRAM_VERSION_MINOR << std::endl;
	ProgramDecorator::run();
}

void HelpProgram::run() {
	std::cout << description_ << std::endl;
	std::ifstream manual("manual.txt");
	if(manual.is_open()) {
		std::cout << manual.rdbuf() << std::endl;
		manual.close();
	}

	ProgramDecorator::run();
}

void ErrorInfoProgram::run() {
	std::cerr << errorMessage_ << std::endl;
	ProgramDecorator::run();
}

