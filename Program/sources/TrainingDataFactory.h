//Created by Daniel Bigos

#include <memory>
#include <vector>
#include <thread>
#include <regex>
#include <boost/tokenizer.hpp>
#include "House.h"

const unsigned THREADS_COUNT = std::thread::hardware_concurrency();

class TrainingDataFactory
{
private:
	std::vector< std::thread > threads_;
	static void createHouseFromRow( unsigned thread_id, std::vector< std::string >* file_rows, std::vector< std::shared_ptr< House > >* training_data );
public:
	TrainingDataFactory();
	void run( std::vector< std::string >* file_rows, std::vector< std::shared_ptr< House > >* training_data );
	~TrainingDataFactory();
};

