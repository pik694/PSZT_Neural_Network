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

		Program() = default;

		virtual void run() = 0;

		virtual ~Program() = default;
	private:
	};

	class SimpleProgram : public Program {
	public:
		SimpleProgram(){
			id_ = ID++;
			std::cerr << id_ << std::endl;
		}
		virtual void run(){}
		virtual ~SimpleProgram(){
			std::cerr << "Destructor" << id_ << std::endl;
		}
		int  id_;
		static int ID;
	};

	

	class SimpleProgramDecorator : public SimpleProgram {
	public:
		SimpleProgramDecorator(std::shared_ptr<SimpleProgram> program): simpleProgram_(program){}

		virtual void run(){
			simpleProgram_->run();
		}

		virtual ~SimpleProgramDecorator(){
			std::cerr << "Decorator destructor" << std::endl;
		}
	private:
		std::shared_ptr<SimpleProgram> simpleProgram_;
	};

	class GetVersionProgram : public SimpleProgramDecorator {
	public:
		GetVersionProgram(std::shared_ptr<SimpleProgram> program): SimpleProgramDecorator(program){}

		virtual void run(){
			std::cout << "Program version : " << PROGRAM_VERSION_MAJOR << "." << PROGRAM_VERSION_MINOR << std::endl;
			SimpleProgramDecorator::run();
		}
		virtual ~GetVersionProgram() = default;
	};

	class HelpProgram : public SimpleProgramDecorator {
	public:
		HelpProgram(std::shared_ptr<SimpleProgram> program, boost::program_options::options_description description) :
				SimpleProgramDecorator(program),
				description_(std::move(description)) {}

		virtual void run(){
			std::cout << description_ << std::endl;
			SimpleProgramDecorator::run();
		}
		virtual ~HelpProgram() = default;

	private:
		boost::program_options::options_description description_;
	};

}

//TODO : too many objects created

#endif //PSZT_NEURAL_NETWORK_PROGRAM_H


