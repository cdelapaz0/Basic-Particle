#pragma once

#include "IBaseState.h"
#include "D3DInclude.h"
#include "DXTKInclude.h"
#include "Camera.h"
#include "Buffer.h"
#include "ParticleEmitter.h"

class D3D;

class MainState : public IBaseState
{
public:
	MainState(D3D* _d3d);
	~MainState();

	// Inherited via IBaseState
	virtual void Enter() override;

	virtual void Exit() override;


	virtual bool Input() override;

	virtual bool Update(float _fDT) override;

	virtual bool Render() override;

private:
	D3D* pD3D;

	Color clearColor;
	Camera mainCamera;

	CameraCBuffer			cbufferCamera;
	ObjectCBuffer			cbufferObject;


	//ID3D11Buffer*			vertexBuffer;

	ID3D11Buffer*			emitterVertexBuffer;
	ID3D11VertexShader*		vertexShader;
	ID3D11PixelShader*		pixelShader;
	ID3D11GeometryShader*	geometryShader;

	ID3D11InputLayout*		inputLayout;

	ID3D11Buffer*			cameraCBuffer;
	ID3D11Buffer*			objectCBuffer;

	ParticleEmitter*		emitter;

};

