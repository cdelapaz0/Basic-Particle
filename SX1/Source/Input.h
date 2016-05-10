#pragma once

#include "KeyBoardState.h"

class Input
{
private:
	static KeyBoardState curr;
	static KeyBoardState prev;

public:
	
	static void Update();

	static bool KeyDown(unsigned int key);
	static bool KeyPressed(unsigned int key);
};

