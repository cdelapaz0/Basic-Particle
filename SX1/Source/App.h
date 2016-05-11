#pragma once

#include <Windows.h>
#include "D3D.h"
#include "StateStack.h"

class App
{
public:
	App();
	~App();

	bool Initialize();
	void Shutdown();
	void Run();

	LRESULT CALLBACK MessageHandler( HWND hWnd, UINT message,
									 WPARAM wParam, LPARAM lParam );

private:
	bool Input();
	bool Update();
	bool Render();

	void InitWindow( int& _width, int& _height, bool _fs = false);
	void ShutWindow();

private:
	LPCWSTR		appName;
	HINSTANCE	hInstance;
	HWND		hWnd;

	D3D*		d3d;
	StateStack  states;
};

static LRESULT CALLBACK WndProc( HWND hWnd, UINT message,
								 WPARAM wParam, LPARAM lParam );

static App* appHandle = nullptr;

