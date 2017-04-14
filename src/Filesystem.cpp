#include "Filesystem.h"
#include <assert.h>

std::string Filesystem::ReadFile( const std::string & filename ) {
	std::ifstream file( filename.c_str(), std::ios::binary );
	assert( file );
	std::string s((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	file.close();
	return s;
}
