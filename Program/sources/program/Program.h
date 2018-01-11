//
// Created by Piotr Żelazko on 05.01.2018.
//

#ifndef PSZT_NEURAL_NETWORK_PROGRAM_H
#define PSZT_NEURAL_NETWORK_PROGRAM_H

#include <mutex>
#include <thread>
#include <boost/program_options.hpp>
#include "program_version.h"

const unsigned SLEEP_TIME = 1;

namespace program
{
    enum class ExecutionMode_E
    {
        TRAIN = 1,
        TRAIN_AND_TEST = 2,
        TEST = 3
    };

	class Program
    {
	public:

		virtual void run(){}

		virtual ~Program() = default;

		static void decrementThreads();
		static int getThreads();
		static void setThreads( int count );


	protected:
		std::vector< std::thread > threadsVec_;

	private:
		static int threads_;
		static std::mutex mutex_;

    };

	
	class ProgramDecorator : public Program
    {
	public:
		 explicit ProgramDecorator( std::unique_ptr< Program > program ):
				program_(std::move(program)){}

		void run() override;

		virtual ~ProgramDecorator() = default;
	private:
		std::unique_ptr< Program > program_;
	};

	class GetVersionProgram : public ProgramDecorator
    {
	public:
		explicit GetVersionProgram( std::unique_ptr< Program > program ): ProgramDecorator( std::move( program ) ) {}

		void run() override;
		virtual ~GetVersionProgram() = default;
	};

	class HelpProgram : public ProgramDecorator
    {
	public:
		HelpProgram( std::unique_ptr<Program> program,
		            boost::program_options::options_description description ) :
				ProgramDecorator( std::move( program ) ),
				description_( std::move( description ) ) {}

		void run() override;

		virtual ~HelpProgram() = default;

	private:
		boost::program_options::options_description description_;
	};

	class ErrorInfoProgram : public ProgramDecorator
    {
	public:
		ErrorInfoProgram( const std::string& errorMessage, std::unique_ptr< Program > program ) :
				ProgramDecorator( std::move( program ) ),
				errorMessage_( errorMessage )
		{}

		void run() override;

		virtual ~ErrorInfoProgram() = default;

	private:
		const std::string errorMessage_;
	};

}

#endif //PSZT_NEURAL_NETWORK_PROGRAM_H

