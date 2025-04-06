#include "pch.h"
#include "PlayerControllerComponent.h"
#include "Player.h"
#include "World.h"
#include "BroadcastManager.h"

PlayerControllerComponent::PlayerControllerComponent(std::weak_ptr<GameObject> owner) : FSMComponent<Protocol::PLAYER_STATE>(owner)
{
	AddState(Protocol::PLAYER_STATE::PLAYER_STATE_IDLE, make_shared<PlayerIdleState>());
	AddState(Protocol::PLAYER_STATE::PLAYER_STATE_MOVE, make_shared<PlayerMoveState>());

	ChangeState(Protocol::PLAYER_STATE::PLAYER_STATE_IDLE);
}

void PlayerControllerComponent::RequestMove(const Vector2& goal)
{
	if (GetCurrentState() == Protocol::PLAYER_STATE::PLAYER_STATE_MOVE)
	{
		Stop();
	}

	auto gameObject = GetGameObject().lock();
	if (gameObject == nullptr) return;

	Log << gameObject->GetId() << " Request Move to " << goal << endl;

	if (Vector2::Distance(goal, Transform()->Position()) <=  0.1f) return;

	World::Instance()->FindPathAsync(Transform()->Position(), goal, 1,
		bind(&PlayerControllerComponent::OnFindPath, this, placeholders::_1));

}

void PlayerControllerComponent::Stop()
{
	if (GetCurrentState() != Protocol::PLAYER_STATE_MOVE) return;

	_goal = Transform()->Position();
	while (_paths.size() > 0)
	{
		_paths.pop();
	}

	ChangeState(Protocol::PLAYER_STATE::PLAYER_STATE_IDLE);
}

void PlayerControllerComponent::OnFindPath(std::queue<IntPoint> path)
{
	auto controller = static_pointer_cast<PlayerControllerComponent>(shared_from_this());
	if (controller == nullptr) return;
	while (!path.empty())
	{
		IntPoint gridPos = path.front();
		path.pop();
		Vector2 worldPos = World::GridPosToWorldPos(gridPos);

		controller->_paths.push(worldPos);
	}

	controller->ChangeState(Protocol::PLAYER_STATE::PLAYER_STATE_MOVE);
}
