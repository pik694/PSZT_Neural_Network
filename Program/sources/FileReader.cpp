#include "FileReader.h"
#include "progress/ProgressStatusManager.h"

using namespace progress;

FileReader::FileReader() = default;

std::vector< std::string > FileReader::getFileRows( const std::string& file_name )
{
	std::vector< std::string > file_rows;
	std::string row;
	file_.open( file_name );
	if (!file_.is_open()){
		throw std::invalid_argument("File could not be opened");
	}

	//first row - headers, no need to store them
	std::getline( file_, row );
	unsigned progress = 0;
	while ( std::getline( file_, row ) )
	{
		++progress;
		file_rows.push_back( row );
		if( progress == PROGRESS_INFO )
		{
			ProgressStatusManager::getInstance()->addProgress( progress );
			ProgressStatusManager::getInstance()->refresh();
			progress = 0;
		}
	}

	ProgressStatusManager::getInstance()->addProgress( --progress );

	file_.close();
	return file_rows;
}

FileReader::~FileReader()
{
	if( file_.is_open() )
		file_.close();
}
