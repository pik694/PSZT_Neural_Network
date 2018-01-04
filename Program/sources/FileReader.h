//Created by Daniel Bigos

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

class FileReader
{
private:
	std::ifstream file_;
public:
	FileReader();
	std::vector< std::string > getFileRows(const std::string& fileName );
	~FileReader();
};

