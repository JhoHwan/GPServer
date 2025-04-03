#include "pch.h"
#include "PlayerControllerComponent.h"
#include "Player.h"
#include "BroadcastManager.h"

PlayerControllerComponent::PlayerControllerComponent(std::weak_ptr<GameObject> owner) : FSMComponent(owner), _isMoving(false), _curState(Protocol::PLAYER_STATE::PLAYER_STATE_IDLE)
{
}

void PlayerControllerComponent::Update(float deltaTime)
{
	if (!_isMoving) return;

	auto gameObject = GetGameObject().lock();
	if (gameObject == nullptr) return;

	BroadcastManager::Instance()->TriggerMove(gameObject->GetId());

	double speed = 600;

	Vector2& position = gameObject->Transform()->Position();
	Vector2 dir = (_goal - position).Normalize();

	position = position + dir * (speed * deltaTime);

	Log << gameObject->GetId() << " Move to " << position << endl;

	if (Vector2::Distance(position, _goal) <= 10.0f)
	{
		position = _goal;
		_isMoving = false;
	}
}

void PlayerControllerComponent::MoveTo(const Vector2& goal)
{
	auto gameObject = GetGameObject().lock();
	if (gameObject == nullptr) return;

	Log << gameObject->GetId() << " Request Move to " << goal << endl;

	if (Vector2::Distance(goal, gameObject->Transform()->Position()) < 10.0f) return;

	_goal = goal;
	_isMoving = true;
}
