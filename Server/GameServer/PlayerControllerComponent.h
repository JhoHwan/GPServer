#pragma once
#include "FSM.h"
#include "IState.h"
#include "Protocol.pb.h"
class Player;

class PlayerControllerComponent : public FSMComponent<Protocol::PLAYER_STATE>
{
public:
	PlayerControllerComponent(std::weak_ptr<GameObject> owner);

	void Update(float deltaTime) override
	{
		FSMComponent<Protocol::PLAYER_STATE>::Update(deltaTime);
	}

public:
	void RequestMove(const Vector2& goal);
	void Stop();

	double GetSpeed() const { return _speed; }

	bool HasPath() const { return !_paths.empty(); }
	Vector2 GetNextPath()
	{
		if (_paths.empty()) return Vector2::Zero();
		Vector2 path = _paths.front();
		_paths.pop();
		return path;
	}

private:
	void OnFindPath(std::queue<IntPoint> path);

private:
	Vector2 _goal;
	std::queue<Vector2> _paths;

	double _speed;

};

class PlayerIdleState : public IState<Protocol::PLAYER_STATE>
{
public:
	PlayerIdleState()  {}
	~PlayerIdleState() {}

public:
	void OnEnter(FSMComponent<Protocol::PLAYER_STATE>& fsm) override {}
	void Update(FSMComponent<Protocol::PLAYER_STATE>& fsm, float deltaTime) override {}
	void OnExit(FSMComponent<Protocol::PLAYER_STATE>& fsm) override {}

	Protocol::PLAYER_STATE GetState() override 
	{ return Protocol::PLAYER_STATE::PLAYER_STATE_IDLE; }
};

class PlayerMoveState : public IState<Protocol::PLAYER_STATE>
{
public:
	PlayerMoveState() : _target(Vector2::Zero()), _controller(nullptr) {}
	~PlayerMoveState() {}

public:
	void OnEnter(FSMComponent<Protocol::PLAYER_STATE>& fsm) override;

	void Update(FSMComponent<Protocol::PLAYER_STATE>& fsm, float deltaTime) override;

	void OnExit(FSMComponent<Protocol::PLAYER_STATE>& fsm) override;

	Protocol::PLAYER_STATE GetState() override { return Protocol::PLAYER_STATE::PLAYER_STATE_MOVE; }

private:
	PlayerControllerComponent* _controller;
	Vector2 _target;
	float _elapsedTime = 0;

	uint32 _frameCount = 0;
};
