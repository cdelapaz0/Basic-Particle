#pragma once

#include <SimpleMath.h>
#include <WICTextureLoader.h>
#include <DDSTextureLoader.h>

#if _DEBUG

#if _WIN64
#pragma comment(lib, "DirectXTKx64d.lib")
#else 
#pragma comment(lib, "DirectXTKx86d.lib")
#endif

#else

#if _WIN64
#pragma comment(lib, "DirectXTKx64.lib")
#else 
#pragma comment(lib, "DirectXTKBx86.lib")
#endif

#endif

using namespace DirectX;
using namespace DirectX::SimpleMath;
