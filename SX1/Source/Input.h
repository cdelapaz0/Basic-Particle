#pragma once

class Input
{
public:
	Input();
	~Input();

	void Initialize();

	void KeyDown( unsigned int keyCode );
	void KeyUp( unsigned int keyCode );

	bool IsKeyDown( unsigned int keyCode );

private:
	bool keys[256];

};

