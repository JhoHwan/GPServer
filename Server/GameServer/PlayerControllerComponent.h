#pragma once
#include "FSMComponent.h"
#include "IState.h"

class Player;

class PlayerControllerComponent : public FSMComponent
{
public:
	PlayerControllerComponent(std::weak_ptr<GameObject> owner);

	void Update(float deltaTime) override;

public:
	bool IsValidPosition();
	void MoveTo(const Vector2& goal);

public:
	inline bool IsMoving() const { return _isMoving; }

private:
	void FindPaths(OUT vector<Vector2> outPaths, const Vector2& start, const Vector2& goal);


private:
	bool _isMoving;

	Vector2 _goal;
	vector<Vector2> _paths;

	Protocol::PLAYER_STATE _curState;

private:
	class IdleState;
};

class PlayerControllerComponent::IdleState : public IState
{
public:
	IdleState() : _state(Protocol::PLAYER_STATE::PLAYER_STATE_IDLE) {}
	~IdleState() {}

public:

	weak_ptr<PlayerControllerComponent> GetOwner()  {}

	void SetOwner(weak_ptr<PlayerControllerComponent> owner) {}

	// IState을(를) 통해 상속됨
	void Update(float deltaTime) override {}

	void OnTransition() override {}

private:
	weak_ptr<PlayerControllerComponent> _owner;

	const Protocol::PLAYER_STATE _state;
};