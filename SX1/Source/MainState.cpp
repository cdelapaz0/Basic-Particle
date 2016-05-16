#include "MainState.h"

#include "D3D.h"
#include "Input.h"
#include "Utilities.h"


MainState::MainState(D3D* _d3d) : IBaseState(StateID::Main)
{
	pD3D = _d3d;
	clearColor = Colors::Red.v;
}

MainState::~MainState()
{

}

void MainState::Enter()
{
	//Init camera
	mainCamera.SetViewport(0.0f, 0.0f, pD3D->GetWidth(), pD3D->GetHeight());
	mainCamera.SetPerspectiveProjection(90.0f, pD3D->GetWidth(), pD3D->GetHeight(), pD3D->GetNearPlane(), pD3D->GetFarPlane());
	mainCamera.SetOrthographicProjection(pD3D->GetWidth(), pD3D->GetHeight(), pD3D->GetNearPlane(), pD3D->GetFarPlane());
	mainCamera.SetViewport(0.0f, 0.0f, pD3D->GetWidth(), pD3D->GetHeight());
	
	//Init vertex shader

	//Init shaders

	//Init input layout

}

void MainState::Exit()
{

}

bool MainState::Input()
{
	if (Input::KeyPressed('R'))
	{
		//Randomize color here
		clearColor = ColorTools::RandomColor();
	}

	return true;
}

bool MainState::Update()
{
	return true;
}

bool MainState::Render()
{
	// Clear the buffers to begin the scene.
	pD3D->BeginScene(clearColor);

	// Set Viewport
	pD3D->GetDeviceContext()->RSSetViewports(1, &mainCamera.GetViewport());

	// Set Camera Constant Buffer

	// Set Other Constant Buffers

	// Set Vertex/Index Buffers
	
	// Set Input Topology

	// Set Input Layout

	// Set Vertex/Geometry/Pixels Shaders

	// Draw

	pD3D->EndScene();

	return true;
}