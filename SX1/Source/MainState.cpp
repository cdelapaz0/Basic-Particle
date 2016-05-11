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

	

	pD3D->EndScene();

	return true;
}