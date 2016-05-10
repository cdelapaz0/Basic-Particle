#pragma once

#include <Windows.h>
#include "Input.h"
#include "Graphics.h"

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
	bool Frame();
	void InitWindow( int& _width, int& _height );
	void ShutWindow();

private:
	LPCWSTR		appName;
	HINSTANCE	hInstance;
	HWND		hWnd;

	Graphics*	graphics;
	Input*		input;
};

static LRESULT CALLBACK WndProc( HWND hWnd, UINT message,
								 WPARAM wParam, LPARAM lParam );

static App* appHandle = nullptr;

