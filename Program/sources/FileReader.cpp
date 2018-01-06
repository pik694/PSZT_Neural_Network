#include "FileReader.h"


FileReader::FileReader() = default;

std::vector< std::string > FileReader::getFileRows( const std::string& file_name )
{
	std::vector< std::string > file_rows;
	std::string row;
	file_.open( file_name );
	//first row - headers, no need to store them
	std::getline( file_, row );
	while ( std::getline( file_, row ) )
		file_rows.push_back( row );

	file_.close();
	return file_rows;
}

FileReader::~FileReader()
{
	if( file_.is_open() )
		file_.close();
}
