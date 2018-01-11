//
// Created by Piotr Żelazko on 05.01.2018.
//

#include <iostream>
#include <fstream>
#include "FileReader.h"
#include "TrainingDataFactory.h"
#include "ProgramInitializer.h"
#include "progress/ProgressStatusManager.h"
#include "neural_network/NeuralNetworkTopology.h"
#include "Serializator.h"

using namespace program;
using namespace program::program_initializer;
using namespace boost::program_options;
using namespace progress;

ProgramInitializer::ProgramInitializer(int argc, const char **argv) :
		infoOptions_("Info options"),
		runOptions_ ("Program arguments"),
		variablesMap_(),
		argc_(argc),
		argv_(argv)
{

		positionalOptions_.add( EPOCH.c_str(), -1 );
		positionalOptions_.add( TOPOLOGY.c_str(), -1 );
        positionalOptions_.add( ETA.c_str(), -1 );
        positionalOptions_.add( PACK.c_str(), -1 );
		positionalOptions_.add( FUNCTION.c_str(), -1 );

	infoOptions_.add_options()
			( command( HELP, "h" ).c_str(), "Show this help message" )
			( command( VERSION, "v" ).c_str(), "Show program version" );
	runOptions_.add_options()
			( command( MODE, "m" ).c_str(), value< ExecutionMode_E >( &executionMode_ )->required(), "Specifies program mode" )
            ( command( DATA, "d" ).c_str(), value< std::string >( &inputFileName_ )->required(), "Specifies input data file" )
            ( command( RESULT, "r" ).c_str(), value< std::string >( &resultPath_ )->default_value( ".\\result" ), "Specifies result path" )
            ( command( LOGGER, "l" ).c_str(), value< std::string >( &loggerFile_ )->default_value( ".\\result\\logger.csv" ), "Specifies logger file" )
            ( command( EPOCH, "e" ).c_str(), value< std::vector< int > >( &epoch_v )->multitoken(), "Specifies epoch count" )
            ( command( TOPOLOGY, "t" ).c_str(), value< std::vector< neural_network::Topology_E > >( &topology_v )->multitoken(), "Specifies topology" )
            ( command( ETA, "c" ).c_str(), value< std::vector< double > >( &eta_v )->multitoken(), "Specifies eta" )
            ( command( NEURAL_NET, "n" ).c_str(), value< std::string >( &neuralNetFile_ ), "Specifies serialized neural network file" )
            ( command( PACK, "p" ).c_str(), value< std::vector< int > >( &batchSize_v )->multitoken(), "Specifies data packs, must be a factor of data size" )
            ( command( FUNCTION, "f" ).c_str(), value< std::vector< neural_network::functions::ActivationFunctions_E > >( &function_v )->multitoken(), "Specifies neural activation function" )
            ( command( TOLERANCE, "b" ).c_str(), value< int  >( &percentage_ )->default_value( -1 ), "Specifies error tolerance" )
            ( command( THREADS, "w" ).c_str(), value< int  >( &threadsForEta_ )->default_value( 0 ), "Specifies threads count for one eta" );
			}

std::string ProgramInitializer::command( std::string longCommand, std::string shortCommand ) const
{
	return ( longCommand + "," + shortCommand );
}

std::unique_ptr< program::Program > ProgramInitializer::getProgram()
{
	std::unique_ptr< Program > program = std::make_unique< Program >();
	try
    {
		parse();
	}
	catch ( boost::program_options::required_option &e )
    {
		if ( variablesMap_.count( HELP ) || variablesMap_.count( VERSION ) )
        {
			if ( variablesMap_.count( HELP ) )
            {
				program = std::make_unique< HelpProgram>( std::move( program ),
				                                        options_description().add( infoOptions_ ).add( runOptions_ ) );
			}
			if ( variablesMap_.count( VERSION ) )
            {
				program = std::make_unique< GetVersionProgram >( std::move( program ) );
			}

			return program;
		}
		else
			return std::make_unique< ErrorInfoProgram >( e.what(), std::move( program ) );
	}
	catch ( std::exception& e )
    {
		return std::make_unique< ErrorInfoProgram >( e.what(), std::move( program ) );
	}


	try
	{
		FileReader fileReader;
		ProgressStatusManager::getInstance()->init( "File reading: " + inputFileName_ );
		std::vector< std::string > file_data = fileReader.getFileRows( inputFileName_ );
		ProgressStatusManager::getInstance()->deinit();

		ProgressStatusManager::getInstance()->init( "Creating training data", file_data.size() );
		std::vector< std::shared_ptr< NormalizedValuesHouse > > training_data( file_data.size() );
		TrainingDataFactory training_data_factory;
		training_data_factory.run( &file_data , &training_data );
		ProgressStatusManager::getInstance()->deinit();

        std::ofstream loggerStream;
		std::ifstream neural_net_file;

        long data_size;

        switch ( executionMode_ )
        {
			case ExecutionMode_E::TRAIN:
                if( epoch_v.empty() || batchSize_v.empty() || function_v.empty() || eta_v.empty() || topology_v.empty() || !loggerFile_.size() || !resultPath_.size() )
                    throw std::runtime_error( "More parameters required." );

				loggerStream.open( loggerFile_ );
				if( !loggerStream.is_open() )
					throw std::runtime_error( "Could not open logger file." );

                if( percentage_ < 0 )
                    throw std::runtime_error( "Invalid percentage specified." );

                if( threadsForEta_ < 1 )
                    throw std::runtime_error( "Invalid threads count for eta specified." );
                data_size = (long)( ( ( 100 - percentage_) / 100.0 ) * training_data.size() );
                for( int i = 0; i < batchSize_v.size(); ++i )
                {
                    if( (data_size % batchSize_v[ i ]) != 0 )
                    {
                        std::string error = "Invalid batch size at: ";
                        error += std::to_string( i );
                        throw std::runtime_error( error );
                    }
                }

                Serializator::getInstance().setLoggerFile( loggerStream );
                Serializator::getInstance().setOuptutDirecotry( resultPath_ );

				return std::make_unique< TrainProgram >( training_data, epoch_v, batchSize_v, function_v, eta_v, topology_v, percentage_, threadsForEta_ );

			case ExecutionMode_E::TRAIN_AND_TEST:
                if( epoch_v.empty() || batchSize_v.empty() || function_v.empty() || eta_v.empty() || topology_v.empty() || !loggerFile_.size() || !resultPath_.size() )
                    throw std::runtime_error( "More parameters required." );

				if( percentage_ < 0 )
					throw std::runtime_error( "Invalid percentage specified." );

				loggerStream.open( loggerFile_ );
				if( !loggerStream.is_open() )
					throw std::runtime_error( "Could not open logger file." );

                data_size = (long)( ( ( 100 - percentage_) / 100.0 ) * training_data.size() );
                for( int i = 0; i < batchSize_v.size(); ++i )
                {
                    if( (data_size % batchSize_v[ i ]) != 0 )
                    {
                        std::string error = "Invalid batch size at: ";
                        error += std::to_string( i );
                        throw std::runtime_error( error );
                    }
                }

                Serializator::getInstance().setLoggerFile( loggerStream );
                Serializator::getInstance().setOuptutDirecotry( resultPath_ );

				return std::make_unique< TrainAndTestProgram >( training_data, epoch_v, batchSize_v, function_v, eta_v, topology_v, percentage_ );

			case ExecutionMode_E::TEST:
                if( batchSize_v.empty() || !neuralNetFile_.size()  )
                    throw std::runtime_error( "More parameters required." );

				if( percentage_ < 0 )
					throw std::runtime_error( "Invalid tolerance specified." );

				neural_net_file.open( neuralNetFile_ );
				if( neural_net_file.is_open() )
					throw std::invalid_argument( "File could not be opened" );

                return std::make_unique< TestProgram >( training_data, neural_net_file, percentage_ );
        }
	}
	catch ( std::exception& e )
    {
		return std::make_unique< ErrorInfoProgram >( e.what(), std::move( program ) );
	}

}

void ProgramInitializer::parse()
{

	options_description all;
	all.add( infoOptions_ );
	all.add( runOptions_ );

	store( parse_command_line( argc_, argv_, all ), variablesMap_ );

	notify( variablesMap_ );
}


namespace boost {
	template<>
	program::ExecutionMode_E lexical_cast(const std::string &name) {

		using string_function_map_t = std::map<const std::string, program::ExecutionMode_E>;

		static const string_function_map_t map = {
				{std::to_string(
						static_cast< int >( program::ExecutionMode_E::TRAIN )),                  program::ExecutionMode_E::TRAIN},
				{std::to_string(
						static_cast< int >( program::ExecutionMode_E::TRAIN_AND_TEST )),         program::ExecutionMode_E::TRAIN_AND_TEST},
				{std::to_string(
						static_cast< int >( program::ExecutionMode_E::TEST )),                   program::ExecutionMode_E::TEST},
		};

        if( map.find( name ) == map.end() )
            throw std::runtime_error( "Invalid execution mode" );

		return map.at(name);

	}
}


namespace boost {
    template<>
    neural_network::functions::ActivationFunctions_E lexical_cast( const std::string &name )
    {

        using string_function_map_t = std::map< const std::string, neural_network::functions::ActivationFunctions_E >;

        static const string_function_map_t map = {
                { std::to_string( static_cast< int >( neural_network::functions::ActivationFunctions_E::step ) ), neural_network::functions::ActivationFunctions_E::step },
                { std::to_string( static_cast< int >( neural_network::functions::ActivationFunctions_E::fastSigmoid ) ), neural_network::functions::ActivationFunctions_E::fastSigmoid },
                { std::to_string( static_cast< int >( neural_network::functions::ActivationFunctions_E::logistic ) ), neural_network::functions::ActivationFunctions_E::logistic },
                { std::to_string( static_cast< int >( neural_network::functions::ActivationFunctions_E::hyperbolicTangent ) ), neural_network::functions::ActivationFunctions_E::hyperbolicTangent },
                { std::to_string( static_cast< int >( neural_network::functions::ActivationFunctions_E::specificAlgebraic ) ), neural_network::functions::ActivationFunctions_E::specificAlgebraic }
        };

        if( map.find( name ) == map.end() )
            throw std::runtime_error( "Invalid function" );

        return map.at(name);
    }
}

namespace boost {
    template<>
    neural_network::Topology_E lexical_cast( const std::string &name )
    {

        using string_function_map_t = std::map< const std::string, neural_network::Topology_E >;

        static const string_function_map_t map = {

                { std::to_string( static_cast< int >( neural_network::Topology_E::_10_10 )), neural_network::Topology_E::_10_10 },
                { std::to_string( static_cast< int >( neural_network::Topology_E::_20_20 )), neural_network::Topology_E::_20_20 },
                { std::to_string( static_cast< int >( neural_network::Topology_E::_20_10 )), neural_network::Topology_E::_20_10 },
                { std::to_string( static_cast< int >( neural_network::Topology_E::_30_15 )), neural_network::Topology_E::_30_15 },
                { std::to_string( static_cast< int >( neural_network::Topology_E::_15_10 )), neural_network::Topology_E::_15_10},
                { std::to_string( static_cast< int >( neural_network::Topology_E::_15_10 )), neural_network::Topology_E::_15_10},
                { std::to_string( static_cast< int >( neural_network::Topology_E::_15_5 )), neural_network::Topology_E::_15_5 },
                { std::to_string( static_cast< int >( neural_network::Topology_E::_5_5 )), neural_network::Topology_E::_5_5 },
                { std::to_string( static_cast< int >( neural_network::Topology_E::_5_5_5 )), neural_network::Topology_E::_5_5_5 },
                { std::to_string( static_cast< int >( neural_network::Topology_E::_10_10_10 )), neural_network::Topology_E::_10_10_10 },
        };

            if( map.find( name ) == map.end() )
                throw std::runtime_error( "Invalid function" );
            return map.at( name );
    }
}

