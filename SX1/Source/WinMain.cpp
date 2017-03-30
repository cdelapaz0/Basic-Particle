// D3D11_WorkSpace.cpp : Defines the entry point for the application.
//


#include "WinMain.h"
#include "App.h"

#include <vld.h>

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow ) 
{
	App* app;
	bool result;


	// Create the system object.
	app = new App;

	// Initialize and run the system object.
	result = app->Initialize();
	if ( result ) 
	{
		app->Run();
	}

	// Shutdown and release the system object.
	app->Shutdown();
	delete app;

	return 0;
}

#if _DEBUG
int main()
{
	return WinMain(0,0,0,0);
}
#endif