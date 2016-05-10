
#include "Graphics.h"
#include "Utilities.h"


Graphics::Graphics() {
	d3d = nullptr;
}


Graphics::~Graphics() {
}

bool Graphics::Initialize( int _width, int _height, HWND _hWnd ) {
	bool result;

	d3d = new D3D;
	if ( !d3d )
		return false;

	result = d3d->Initialize( _width, _height, VSYNC_ENABLED, _hWnd,
							  FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR );
	if ( !result ) {
		MessageBox( _hWnd, L"Could not initialize Direct3D", L"Error",
					MB_OK );
		return false;
	}


	return true;
}

void Graphics::Shutdown() {
	SAFE_SHUTDOWN( d3d );
}

bool Graphics::Frame() {

	Render();
	return true;
}

bool Graphics::Render( ) {
	Matrix viewMatrix, projectionMatrix, worldMatrix;

	// Clear the buffers to begin the scene.
	d3d->BeginScene( 1.0f, 0.0f, 0.0f, 1.0f );


	d3d->EndScene();

	return true;
}
