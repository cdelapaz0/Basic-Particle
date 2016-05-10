#include "Input.h"


Input::Input() {
}


Input::~Input() {
}

void Input::Initialize() {
	for ( int i = 0; i < 256; ++i )
	{
		keys[i] = false;
	}
}

void Input::KeyDown( unsigned int keyCode ) {
	keys[keyCode] = true;
}

void Input::KeyUp( unsigned int keyCode ) {
	keys[keyCode] = false;
}

bool Input::IsKeyDown( unsigned int keyCode ) {
	return keys[keyCode];
}
