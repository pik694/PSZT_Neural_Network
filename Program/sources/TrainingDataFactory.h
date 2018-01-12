//Created by Daniel Bigos

#include <memory>
#include <vector>
#include <thread>
#include <regex>
#include <boost/tokenizer.hpp>
#include "house/NormalizedValuesHouse.h"


using namespace house;

class TrainingDataFactory
{
private:
	std::vector< std::thread > threads_;
	static void createHouseFromRow( unsigned thread_id, std::vector< std::string >* file_rows, std::vector< NormalizedValuesHouse >* training_data );
public:
	TrainingDataFactory();
	void run( std::vector< std::string >* file_rows, std::vector<NormalizedValuesHouse>* training_data );
	~TrainingDataFactory();
};

