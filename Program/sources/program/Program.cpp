#include <iostream>
#include "Program.h"

using namespace program;

void program::ProgramDecorator::run()
{
    program_->run();
}

void GetVersionProgram::run()
{
    std::cout << "Program version : " << PROGRAM_VERSION_MAJOR << "." << PROGRAM_VERSION_MINOR << std::endl;
    ProgramDecorator::run();
}

void HelpProgram::run()
{
    std::cout << description_ << std::endl;
    ProgramDecorator::run();
}

void ErrorInfoProgram::run()
{
    std::cerr << errorMessage_ << std::endl;
    ProgramDecorator::run();
}

namespace boost
{
    template<>
    program::ExecutionMode_E lexical_cast( const std::string &name )
    {

        using string_function_map_t = std::map< const std::string, ExecutionMode_E>;

        static const string_function_map_t map = {
                { std::to_string( static_cast< int >( ExecutionMode_E::TRAIN ) ), ExecutionMode_E::TRAIN },
                { std::to_string( static_cast< int >( ExecutionMode_E::TRAIN_AND_TEST ) ), ExecutionMode_E::TRAIN_AND_TEST },
                { std::to_string( static_cast< int >( ExecutionMode_E::TEST ) ), ExecutionMode_E::TEST },
        };

        return map.at( name );
    }

}