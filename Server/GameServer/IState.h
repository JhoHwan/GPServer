#pragma once

class FSMComponent;

class IState
{
public:
	virtual void Update(float deltaTime) = 0;
	virtual void OnTransition() = 0;
};