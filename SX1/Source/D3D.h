#pragma once

#include "WindowsInclude.h"
#include "D3DInclude.h"
#include "DXTKInclude.h"

class D3D
{
public:
	D3D();
	~D3D();

	bool Initialize( int _width, int _height, bool _vsync, HWND _hWnd, bool _fs,
					 float _depth, float _near );
	void Shutdown();

	void BeginScene( float r, float g, float b, float a );
	void EndScene();

	ID3D11Device*			GetDevice();
	ID3D11DeviceContext*	GetDeviceContext();

	Matrix GetProjectionMatrix( );
	Matrix GetWorldMatrix( );
	Matrix GetOrthoMatrix( );

	void GetVideoCardInfo( char* cardName, int& memory );

	//void* operator new( size_t size );
	//void operator delete( void* ptr );

private:
	bool vsyncEnabled;
	int videoCardMemory;
	char videoCardDescription[128];

	IDXGISwapChain*				swapChain;
	ID3D11Device*				device;
	ID3D11DeviceContext*		deviceContext;
	ID3D11RenderTargetView*		renderTargetView;
	ID3D11Texture2D*			depthStencilBuffer;
	ID3D11DepthStencilState*	depthStencilState;
	ID3D11DepthStencilView*		depthStencilView;
	ID3D11RasterizerState*		rasterState;
	Matrix						projectionMatrix;
	Matrix						worldMatrix;
	Matrix						orthoMatrix;
};

