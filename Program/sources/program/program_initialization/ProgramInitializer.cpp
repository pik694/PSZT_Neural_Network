//
// Created by Piotr Żelazko on 05.01.2018.
//

#include <iostream>
#include <fstream>
#include "neural_network/NeuralNetwork.h"
#include "FileReader.h"
#include "TrainingDataFactory.h"
#include "ProgramInitializer.h"
#include "progress/ProgressStatusManager.h"
#include "neural_network/NeuralNetworkTopology.h"


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
		positionalOptions_.add( TOLERANCE.c_str(), -1 );

	infoOptions_.add_options()
			( command( HELP, "h" ).c_str(), "Show this help message" )
			( command( VERSION, "v" ).c_str(), "Show program version" );
	runOptions_.add_options()
			( command( MODE, "m" ).c_str(), value< ExecutionMode_E >( &executionMode_ )->required(), "Specifies program mode" )
            ( command( DATA, "d" ).c_str(), value< std::string >( &inputFileName_ )->required(), "Specifies input data file" )
            ( command( EPOCH, "e" ).c_str(), value< std::vector< int > >( &epoch_v )->multitoken(), "Specifies epoch count" )
            ( command( TOPOLOGY, "t" ).c_str(), value< std::vector< neural_network::Topology_E > >( &topology_v )->multitoken(), "Specifies topology" )
            ( command( ETA, "c" ).c_str(), value< std::vector< double > >( &eta_v )->multitoken(), "Specifies eta" )
            ( command( NEURAL_NET, "n" ).c_str(), value< std::string >( &neuralNetFile_ ), "Specifies serialized neural network file" )
            ( command( PACK, "p" ).c_str(), value< std::vector< int > >( &pack_v )->multitoken(), "Specifies data packs, must be a factor of data size" )
            ( command( FUNCTION, "f" ).c_str(), value< std::vector< neural_network::functions::ActivationFunctions_E > >( &function_v )->multitoken(), "Specifies neural activation function" )
            ( command( TOLERANCE, "b" ).c_str(), value< std::vector< int > >( &tolerance_v )->multitoken(), "Specifies error tolerance" );
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

        switch ( executionMode_ )
        {
			case ExecutionMode_E::TRAIN:
                if( !epoch_v.size() || !pack_v.size() || !function_v.size() || !eta_v.size() || !topology_v.size() )
                    throw std::runtime_error( "More parameters required." );

				return std::make_unique< TrainProgram >( &training_data, &epoch_v, &pack_v, &function_v, &eta_v, &topology_v );

			case ExecutionMode_E::TRAIN_AND_TEST:
                if( !epoch_v.size() || !pack_v.size() || !function_v.size() || !eta_v.size() || !topology_v.size() || !tolerance_v.size() )
                    throw std::runtime_error( "More parameters required." );

                return std::make_unique< TrainAndTestProgram >( &training_data, &epoch_v, &pack_v, &function_v, &eta_v, &topology_v, &tolerance_v );

			case ExecutionMode_E::TEST:
                if( !pack_v.size() || !neuralNetFile_.size() || !tolerance_v.size() )
                    throw std::runtime_error( "More parameters required." );

				std::ifstream neural_net_file;
				neural_net_file.open( neuralNetFile_ );
				if( neural_net_file.is_open() )
					throw std::invalid_argument( "File could not be opened" );

                return std::make_unique< TestProgram >( &training_data, &neural_net_file, &pack_v, &tolerance_v );
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
                { std::to_string( static_cast< int >( neural_network::Topology_E ::JakaKolwiek) ), neural_network::Topology_E::JakaKolwiek },
              };

            if( map.find( name ) == map.end() )
                throw std::runtime_error( "Invalid function" );
            return map.at( name );
    }
}

