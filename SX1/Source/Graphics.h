#pragma once

#include <Windows.h>
#include "D3D.h"

const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

class Graphics
{
public:
	Graphics();
	~Graphics();

	bool Initialize(int _width, int _height, HWND _hWnd);
	void Shutdown();
	bool Frame();

private:
	bool Render();

private:
	D3D* d3d;
};

