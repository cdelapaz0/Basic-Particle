
#include "Utilities.h"
#include <string>
#include <random>

#define DIR_SEPARATOR L"/"

std::random_device rd;
std::mt19937 gen(rd());

std::vector<std::wstring> String::Split( std::wstring str, const std::wstring& separator ) {
	std::vector<std::wstring> Results;

	std::size_t found;
	found = str.find_first_of( separator );
	while ( found != std::wstring::npos ) {
		if ( found > 0 ) {
			Results.push_back( str.substr( 0, found ) );
		}

		str = str.substr( found + 1 );
		found = str.find_first_of( separator );
	}

	if ( str.length() > 0 ) {
		Results.push_back( str );
	}

	return Results;
}

std::wstring String::GetFilenameExt( std::wstring Filename ) {
	std::vector<std::wstring> Parts = Split( Filename, L"." );

	return ( Parts.size() <= 1 ? L"" : Parts[Parts.size() - 1] );
}

std::wstring String::GetFilenameWithoutExt( std::wstring Filename ) {
	std::vector<std::wstring> Parts = Split( Filename, DIR_SEPARATOR );
	std::wstring NewFilename = Parts[Parts.size() - 1];

	// To Do: Filename could potentially have one or more dots
	Parts = Split( NewFilename, L"." );
	NewFilename = Parts[0];

	return NewFilename;
}

Color ColorTools::RandomColor()
{
	float a = Random::NextFloat();
	float r = Random::NextFloat();
	float g = Random::NextFloat();
	float b = Random::NextFloat();
	return Color(r, g, b, a);
}

float Random::NextFloat()
{
	return std::generate_canonical<float, 10>(gen);
}

float Random::NextFloat(float min, float max)
{
	std::uniform_real_distribution<float> dis(min, max);
	return dis(gen);
}
