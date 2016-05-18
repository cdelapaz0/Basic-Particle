#pragma once

#include "D3DInclude.h"

struct CameraCBuffer
{
	Matrix viewMatrix;
	Matrix projectionMatrix;
};

struct ObjectCBuffer
{
	Matrix worldMatrix;
};
