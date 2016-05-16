#pragma once

#include "IBaseState.h"
#include "D3DInclude.h"
#include "DXTKInclude.h"
#include "Camera.h"

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

	virtual bool Update() override;

	virtual bool Render() override;

private:
	D3D* pD3D;

	Color clearColor;

	Camera mainCamera;
};

