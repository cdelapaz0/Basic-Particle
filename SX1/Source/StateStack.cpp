#include "StateStack.h"

void StateStack::push(IBaseState * _state)
{
	stack.push_front(_state);
}

void StateStack::pop()
{
	stack.pop_front();
}

IBaseState * StateStack::front()
{
	if (stack.empty())
		return nullptr;
	return stack.front();
}
