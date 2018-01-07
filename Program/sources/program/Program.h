//
// Created by Piotr Żelazko on 05.01.2018.
//

#ifndef PSZT_NEURAL_NETWORK_PROGRAM_H
#define PSZT_NEURAL_NETWORK_PROGRAM_H

#include <boost/program_options.hpp>
#include "program_version.h"

namespace program {


	class Program {
	public:

		virtual void run(){}

		virtual ~Program() = default;
	private:
	};

	
	class ProgramDecorator : public Program {
	public:
		 explicit ProgramDecorator(std::unique_ptr<Program> program):
				program_(std::move(program)){}

		void run() override {
			program_->run();
		}

		virtual ~ProgramDecorator() = default;
	private:
		std::unique_ptr<Program> program_;
	};

	class GetVersionProgram : public ProgramDecorator {
	public:
		explicit GetVersionProgram(std::unique_ptr<Program> program): ProgramDecorator(std::move(program)){}

		void run() override {
			std::cout << "Program version : " << PROGRAM_VERSION_MAJOR << "." << PROGRAM_VERSION_MINOR << std::endl;
			ProgramDecorator::run();
		}
		virtual ~GetVersionProgram() = default;
	};

	class HelpProgram : public ProgramDecorator {
	public:
		HelpProgram(std::unique_ptr<Program> program,
		            boost::program_options::options_description description) :
				ProgramDecorator(std::move(program)),
				description_(std::move(description)) {}

		void run() override {
			std::cout << description_ << std::endl;
			ProgramDecorator::run();
		}
		virtual ~HelpProgram() = default;

	private:
		boost::program_options::options_description description_;
	};

	class ErrorInfoProgram : public ProgramDecorator{
	public:
		ErrorInfoProgram(const std::string& errorMessage, std::unique_ptr<Program> program) :
				errorMessage_(errorMessage),
				ProgramDecorator(std::move(program)) {}

		void run() override {
			std::cerr << errorMessage_ << std::endl;
			ProgramDecorator::run();
		}
		virtual ~ErrorInfoProgram() = default;

	private:
		const std::string errorMessage_;
	};

}

#endif //PSZT_NEURAL_NETWORK_PROGRAM_H

