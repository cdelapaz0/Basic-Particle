#include "Input.h"
#include "WindowsInclude.h"

KeyBoardState Input::curr;
KeyBoardState Input::prev;

bool Input::KeyDown(unsigned int key)
{
	return curr[key];
}

bool Input::KeyPressed(unsigned int key)
{
	return (curr[key] && !prev[key]);
}

void Input::Update()
{
	bool keys[256];
	for (int i = 0; i < 256; ++i)
	{
		keys[i] = (GetAsyncKeyState(i) != 0);
	}

	prev = curr;
	curr.SetKeys(keys, 256);
}
