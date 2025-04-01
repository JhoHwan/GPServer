#include "pch.h"
#include "PlayerControllerComponent.h"
#include "Player.h"
#include "BroadcastManager.h"

PlayerControllerComponent::PlayerControllerComponent(std::weak_ptr<GameObject> owner) : Component(owner), _isMoving(false)
{
}

void PlayerControllerComponent::Update(float deltaTime)
{
	if (!_isMoving) return;

	auto gameObject = GetGameObject().lock();
	if (gameObject == nullptr) return;

	BroadcastManager::Instance()->TriggerMove(gameObject->GetID());

	double speed = 600;

	Vector2& position = gameObject->Transform()->Position();
	Vector2 dir = (_goal - position).Normalize();

	position = position + dir * (speed * deltaTime);


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

	cout << gameObject->GetID() << " Request Move to" << goal << endl;


	if (Vector2::Distance(goal, gameObject->Transform()->Position()) < 10.0f) return;

	_goal = goal;
	_isMoving = true;
}
