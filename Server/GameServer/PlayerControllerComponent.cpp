#include "pch.h"
#include "PlayerControllerComponent.h"
#include "Player.h"
#include "BroadcastManager.h"

PlayerControllerComponent::PlayerControllerComponent(std::weak_ptr<GameObject> owner) : FSMComponent<Protocol::PLAYER_STATE>(owner)
{
	AddState(Protocol::PLAYER_STATE::PLAYER_STATE_IDLE, make_shared<PlayerIdleState>());
	AddState(Protocol::PLAYER_STATE::PLAYER_STATE_MOVE, make_shared<PlayerMoveState>());

	ChangeState(Protocol::PLAYER_STATE::PLAYER_STATE_IDLE);
}

void PlayerControllerComponent::MoveTo(const Vector2& goal)
{
	auto gameObject = GetGameObject().lock();
	if (gameObject == nullptr) return;

	while (_paths.size() > 0)
	{
		_paths.pop();
	}

	Log << gameObject->GetId() << " Request Move to " << goal << endl;

	if (Vector2::Distance(goal, Transform()->Position()) <=  0.1f) return;

	_paths.push(goal);

	ChangeState(Protocol::PLAYER_STATE::PLAYER_STATE_MOVE);
}