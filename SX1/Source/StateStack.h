#pragma once

class IBaseState;
#include <list>

class StateStack
{
public:
	void push(IBaseState *_state);
	void pop();

	IBaseState* front();

private:
	std::list<IBaseState*> stack;
};