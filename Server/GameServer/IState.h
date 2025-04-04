#pragma once

template<typename T>
class FSMComponent;

template<typename T>
class IState
{
public:
	virtual void OnEnter(FSMComponent<T>& fsm) = 0;
	virtual void Update(FSMComponent<T>& fsm, float deltaTime) = 0;
	virtual void OnExit(FSMComponent<T>& fsm) = 0;

	virtual T GetState() = 0;
};