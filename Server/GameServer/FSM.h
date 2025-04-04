#pragma once

#include "IState.h"

template<typename T>
class FSMComponent : public Component
{
public:
	FSMComponent(std::weak_ptr<GameObject> owner) : Component(owner) {}

	virtual ~FSMComponent() {}

public:
	void AddState(T state, std::shared_ptr<IState<T>> newState)
	{
		auto it = _states.find(state);
		if (it != _states.end()) return;

		_states.insert(std::make_pair(state, newState));
	}

	inline T GetCurrentState() const { return _curState; }
	void ChangeState(T newState)
	{
		if (_curState == nullptr)
		{
			_curState = _states[newState];
			return;
		}

		if (_curState->GetState() == newState) return;

		auto it = _states.find(newState);
		if (it == _states.end()) return;

		if (_curState != nullptr)
		{
			_curState->OnExit(*this);
		}

		_curState = it->second;
		_curState->OnEnter(*this);
	}

	virtual void Update(float deltaTime)
	{
		if (_curState == nullptr) return;
		_curState->Update(*this, deltaTime);
	}

private:
	std::unordered_map<T, std::shared_ptr<IState<T>>> _states;
	std::shared_ptr<IState<T>> _curState;
};	

