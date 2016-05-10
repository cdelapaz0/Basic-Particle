//#include "stdafx.h"
#include "App.h"


App::App() {
	input = nullptr;
	graphics = nullptr;
}

App::~App() {
}

bool App::Initialize() {
	int width, height;
	bool result;

	width = height = 0;

	InitWindow( width, height );

	input = new Input;
	if ( !input ) {
		return false;
	}

	input->Initialize();

	graphics = new Graphics;
	if ( !graphics ) {
		return false;
	}

	result = graphics->Initialize( width, height, hWnd );
	if ( !result ) {
		return false;
	}

	return true;
}

void App::Shutdown() {
	if ( graphics ) {
		graphics->Shutdown();
		delete graphics;
		graphics = nullptr;
	}

	if ( input ) {
		delete input;
		input = nullptr;
	}

	ShutWindow();
}

void App::Run() {
	MSG msg;
	bool done, result;

	ZeroMemory( &msg, sizeof( MSG ) );

	done = false;

	while ( !done ) {
		if ( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) ) {
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}

		if ( msg.message == WM_QUIT ) {
			done = true;
		}
		else {
			result = Frame();
			if ( !result ) {
				done = true;
			}
		}
	}
}

bool App::Frame() {
	bool result;

	if ( input->IsKeyDown( VK_ESCAPE ) ) {
		return false;
	}

	result = graphics->Frame();
	if ( !result ) {
		return false;
	}

	return true;
}

void App::InitWindow( int& _width, int& _height ) {
	WNDCLASSEX wc;
	DEVMODE dmScreenSettings;
	int posX, posY;

	appHandle = this;

	hInstance = GetModuleHandle( NULL );

	appName = L"Engine";

	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon( NULL, IDI_WINLOGO );
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor( NULL, IDC_ARROW );
	wc.hbrBackground = (HBRUSH)GetStockObject( BLACK_BRUSH );
	wc.lpszMenuName = NULL;
	wc.lpszClassName = appName;
	wc.cbSize = sizeof( WNDCLASSEX );

	RegisterClassEx( &wc );

	_width = GetSystemMetrics( SM_CXSCREEN );
	_height = GetSystemMetrics( SM_CYSCREEN );

	if ( FULL_SCREEN ) {
		memset( &dmScreenSettings, 0, sizeof( dmScreenSettings ) );
		dmScreenSettings.dmSize = sizeof( dmScreenSettings );
		dmScreenSettings.dmPelsWidth = (unsigned long)_width;
		dmScreenSettings.dmPelsHeight = (unsigned long)_height;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		ChangeDisplaySettings( &dmScreenSettings, CDS_FULLSCREEN );

		posX = posY = 0;
	}
	else {
		_width = 800;
		_height = 600;

		posX = ( GetSystemMetrics( SM_CXSCREEN ) - _width ) / 2;
		posY = ( GetSystemMetrics( SM_CYSCREEN ) - _height ) / 2;
	}

	hWnd = CreateWindowEx( WS_EX_APPWINDOW, appName, appName,
						   WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
							 posX, posY, _width, _height, NULL, NULL, hInstance, NULL );

	ShowWindow( hWnd, SW_SHOW );
	SetForegroundWindow( hWnd );
	SetFocus( hWnd );

	//ShowCursor( false );

	return;
}

void App::ShutWindow() {
	//ShowCursor( true );

	if ( FULL_SCREEN ) {
		ChangeDisplaySettings( NULL, 0 );
	}

	DestroyWindow( hWnd );
	hWnd = nullptr;

	UnregisterClass( appName, hInstance );
	hInstance = nullptr;

	appHandle = nullptr;
}

LRESULT CALLBACK App::MessageHandler( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam ) {
	switch ( message ) {
		case WM_KEYDOWN:
			input->KeyDown( (unsigned int)wParam );
			return 0;
		case WM_KEYUP:
			input->KeyUp( (unsigned int)wParam );
			return 0;
		default:
			return DefWindowProc( hWnd, message, wParam, lParam );
	}
}

static LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam ) {
	switch ( message ) {
		case WM_DESTROY:
			PostQuitMessage( 0 );
			return 0;
		case WM_CLOSE:
			PostQuitMessage( 0 );
			return 0;
		default:
			return appHandle->MessageHandler( hWnd, message, wParam, lParam );
	}
}
