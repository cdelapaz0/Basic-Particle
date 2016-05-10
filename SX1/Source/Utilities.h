#pragma once

#include <vector>
#include <string>


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


namespace String  {

	std::vector<std::wstring> Split( std::wstring str, const std::wstring& separator );

	std::wstring GetFilenameExt( std::wstring Filename );

	std::wstring GetFilenameWithoutExt( std::wstring Filename );

}
