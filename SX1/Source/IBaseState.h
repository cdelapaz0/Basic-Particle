#pragma once

enum class StateID
{
	Main,
	Test,
	Max,
};

class IBaseState
{
	StateID id;

public:
	IBaseState(StateID _id) { id = _id; }

	virtual void Enter() = 0;
	virtual void Exit() = 0;

	virtual bool Input() = 0;
	virtual bool Update(float _fDT) = 0;
	virtual bool Render() = 0;

	StateID GetID() { return id; }
};