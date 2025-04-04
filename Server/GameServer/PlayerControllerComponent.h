#pragma once
#include "FSM.h"
#include "IState.h"

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
	void MoveTo(const Vector2& goal);
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
	Vector2 _goal;
	std::queue<Vector2> _paths;

	double _speed = 600;

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

	Protocol::PLAYER_STATE GetState() override { return Protocol::PLAYER_STATE::PLAYER_STATE_IDLE; }
};

class PlayerMoveState : public IState<Protocol::PLAYER_STATE>
{
public:
	PlayerMoveState() : _target(Vector2::Zero()), _controller(nullptr) {}
	~PlayerMoveState() {}

public:
	void OnEnter(FSMComponent<Protocol::PLAYER_STATE>& fsm) override 
	{
		_controller = static_cast<PlayerControllerComponent*>(&fsm);
		if (!_controller->HasPath())
		{
			fsm.ChangeState(Protocol::PLAYER_STATE::PLAYER_STATE_IDLE);
			return;
		}

		_target = _controller->GetNextPath();
		_frameCount = 0;
	}

	void Update(FSMComponent<Protocol::PLAYER_STATE>& fsm ,float deltaTime) override
	{
		auto gameObject = fsm.GetGameObject().lock();
		if (gameObject == nullptr) return;

		_elapsedTime += deltaTime;
		_frameCount++;

		_controller = static_cast<PlayerControllerComponent*>(&fsm);
		double speed = _controller->GetSpeed();

		Vector2& position = gameObject->Transform()->Position();
		Vector2 dir = (_target - position).Normalize();

		float moveDistance = speed * deltaTime;
		moveDistance = min(moveDistance, Vector2::Distance(position, _target));

		position = position + dir * moveDistance;

		//Log << gameObject->GetId() << " Move to " << position << endl;

		if (Vector2::Distance(position, _target) > 0.01f)
		{
			BroadcastManager::Instance()->RegisterBroadcastMove(CalculateBroadcastLevel(), gameObject->GetId(), position, Protocol::PLAYER_STATE_MOVE);
			return;
		}


		position = _target;
		Log << gameObject->GetId() << " Arrived to " << position << endl;

		if (!_controller->HasPath())
		{
			fsm.ChangeState(Protocol::PLAYER_STATE::PLAYER_STATE_IDLE);
			return;
		}
		else
		{
			_target = _controller->GetNextPath();

			BroadcastManager::Instance()->RegisterBroadcastMove(BroadcastLevel::ALL, gameObject->GetId(), position, Protocol::PLAYER_STATE_MOVE);
		}

	}

	void OnExit(FSMComponent<Protocol::PLAYER_STATE>& fsm) override
	{
		auto gameObject = fsm.GetGameObject().lock();
		if (gameObject == nullptr) return;

		BroadcastManager::Instance()->RegisterBroadcastMove(BroadcastLevel::ALL, gameObject->GetId(), fsm.Transform()->Position(), Protocol::PLAYER_STATE_IDLE);
	}

	Protocol::PLAYER_STATE GetState() override { return Protocol::PLAYER_STATE::PLAYER_STATE_MOVE; }

private:
	BroadcastLevel CalculateBroadcastLevel()
	{
		if (_frameCount  % 30 == 0)
		{
			_elapsedTime = 0;
			return BroadcastLevel::Level2;
		}

		if (_frameCount % 10 == 0)
		{
			_elapsedTime = 0;
			return BroadcastLevel::Level1;
		}

		return BroadcastLevel::Level0;
	}

private:
	PlayerControllerComponent* _controller;
	Vector2 _target;
	float _elapsedTime = 0;

	uint32 _frameCount = 0;
};
