#pragma once

class KeyBoardState
{
public:
	KeyBoardState();
	~KeyBoardState();
	KeyBoardState(const KeyBoardState& that);

	KeyBoardState& operator=(const KeyBoardState& that);

	bool operator[](const unsigned int index) const;
	bool operator[](unsigned int index);

	void SetKeys(const bool* _keys, int numKeys);

private:
	bool* keys;
};

