#pragma once

#include <vector>
#include <string>

#include "DXTKInclude.h"


#define SAFE_RELEASE(x)\
{ \
	if ( x != nullptr ) {\
		x->Release(); \
		x = nullptr; \
	}\
}

#define SAFE_SHUTDOWN(x)\
{\
	if ( x != nullptr ) {\
		x->Shutdown(); \
		delete x; \
		x = nullptr; \
	}\
}

#define SAFE_DELETE(x)\
{\
	if ( x != nullptr ) {\
		delete x; \
		x = nullptr; \
	}\
}

namespace Random
{
	float NextFloat();
	float NextFloat(float min, float max);
}

namespace ColorTools
{
	Color RandomColor();
}

namespace String  
{

	std::vector<std::wstring> Split( std::wstring str, const std::wstring& separator );

	std::wstring GetFilenameExt( std::wstring Filename );

	std::wstring GetFilenameWithoutExt( std::wstring Filename );

}

namespace Math
{
	float Lerp(float a, float b, float t);
}
