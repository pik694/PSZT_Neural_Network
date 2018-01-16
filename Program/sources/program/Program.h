//
// Created by Piotr Żelazko on 05.01.2018.
//

#ifndef PSZT_NEURAL_NETWORK_PROGRAM_H
#define PSZT_NEURAL_NETWORK_PROGRAM_H

#include <mutex>
#include <thread>
#include <boost/program_options.hpp>
#include <tuple>
#include "program_version.h"
#include "neural_network/NeuralNetwork.h"
#include "neural_network/NeuralNetworkTopology.h"
#include "house/NormalizedValuesHouse.h"
#include "neural_network/ActivationFunctionsBank.h"
#include "Serializator.h"

const unsigned SLEEP_TIME = 1;

const int NEURAL_NETWORK = 0;
const int EPOCHS = 1;
const int BATCH_SIZE = 2;
const int ETA = 3;
const int TEST_PERCENTAGE = 4;
const int MSE = 5;
const int ACTIVATION_FUNCTION = 6;

typedef std::tuple< neural_network::NeuralNetwork<house::NormalizedValuesHouse>, const int, const int, const double, const int, double , const neural_network::functions::ActivationFunctions_E > ConfigTuple;


namespace program
{
    enum class ExecutionMode_E
    {
        TRAIN = 1,
        TRAIN_WITH_TIMER = 2,
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

