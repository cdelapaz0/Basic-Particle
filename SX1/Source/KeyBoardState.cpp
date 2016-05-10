#include "KeyBoardState.h"

KeyBoardState::KeyBoardState()
{
	keys = new bool[256];
	for (int i = 0; i < 256; ++i)
	{
		keys[i] = 0;
	}
}

KeyBoardState::KeyBoardState(const KeyBoardState& that)
{
	keys = new bool[256];
	SetKeys(that.keys, 256);
}

KeyBoardState::~KeyBoardState()
{
	delete[] keys;
}

KeyBoardState& KeyBoardState::operator=(const KeyBoardState& that)
{
	if (this != &that)
	{
		delete[] keys;
		keys = new bool[256];
		SetKeys(that.keys, 256);
	}

	return *this;
}

bool KeyBoardState::operator[](const unsigned int index) const
{
	return keys[index];
}

bool KeyBoardState::operator[](unsigned int index)
{
	return keys[index];
}

void KeyBoardState::SetKeys(const bool* _keys, int numKeys)
{
	for (int i = 0; i < numKeys; i++)
	{
		keys[i] = _keys[i];
	}
}
