#include "pch.h"
#include "PlayerControllerComponent.h"
#include "Player.h"
#include "World.h"
#include "BroadcastManager.h"

PlayerControllerComponent::PlayerControllerComponent(std::weak_ptr<GameObject> owner) : FSMComponent<Protocol::PLAYER_STATE>(owner), _speed(600), _rotateSpeed(360)
{
	AddState(Protocol::PLAYER_STATE::PLAYER_STATE_IDLE, make_shared<PlayerIdleState>());
	AddState(Protocol::PLAYER_STATE::PLAYER_STATE_MOVE, make_shared<PlayerMoveState>());

	ChangeState(Protocol::PLAYER_STATE::PLAYER_STATE_IDLE);
}

void PlayerControllerComponent::RequestMove(const Vector3& goal)
{
	if (GetCurrentState() == Protocol::PLAYER_STATE::PLAYER_STATE_MOVE)
	{
		Stop();
	}

	auto gameObject = GetGameObject().lock();
	if (gameObject == nullptr) return;

	Log << gameObject->GetId() << " Request Move to " << goal << endl;

    if (Vector3::Distance(goal, Transform()->Position()) <=  0.1f) return;

	//World::Instance()->FindPathAsync(Transform()->Position(), goal, 1,
		//bind(&PlayerControllerComponent::OnFindPath, this, placeholders::_1));

	World::Instance()->FindPathAsync(Transform()->Position(), goal, bind(&PlayerControllerComponent::OnFindPath, this, placeholders::_1));

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

void PlayerControllerComponent::OnFindPath(std::queue<Vector3> path)
{
	auto controller = static_pointer_cast<PlayerControllerComponent>(shared_from_this());
	if (controller == nullptr) return;
	while (!path.empty())
	{
		Vector3 pos = path.front();
		path.pop();

		controller->_paths.push(pos);
	}

	controller->ChangeState(Protocol::PLAYER_STATE::PLAYER_STATE_MOVE);
}

////////////////////////////
// PlayerMoveState Class ///
////////////////////////////

void PlayerMoveState::OnEnter(FSMComponent<Protocol::PLAYER_STATE>& fsm)
{
	auto gameObject = fsm.GetGameObject().lock();
	if (gameObject == nullptr) return;

	_controller = static_cast<PlayerControllerComponent*>(&fsm);
	if (!_controller->HasPath())
	{
		fsm.ChangeState(Protocol::PLAYER_STATE::PLAYER_STATE_IDLE);
		return;
	}
	_targetPosition = _controller->GetNextPath();

	Vector3& position = gameObject->Transform()->Position();
	YawRotation& yaw = gameObject->Transform()->Rotation();

	Vector3 newDir = _targetPosition - position;
	yaw = YawRotation::GetYawFromDirection(newDir);

	BroadcastManager::Instance()->RegisterBroadcastMove(BroadcastLevel::ALL, gameObject->GetId(), _targetPosition, yaw, Protocol::PLAYER_STATE_MOVE);

	_frameCount = 0;
}

void PlayerMoveState::Update(FSMComponent<Protocol::PLAYER_STATE>& fsm, float deltaTime)
{
	auto gameObject = fsm.GetGameObject().lock();
	if (gameObject == nullptr) return;

	double speed = _controller->GetSpeed();

	Vector3& position = gameObject->Transform()->Position();
	YawRotation& yaw = gameObject->Transform()->Rotation();

	if (Vector3::Distance(position, _targetPosition) <= 1)
	{
		position = _targetPosition;

		if (!_controller->HasPath())
		{
			fsm.ChangeState(Protocol::PLAYER_STATE::PLAYER_STATE_IDLE);
			return;
		}

		_targetPosition = _controller->GetNextPath();

		Vector3 newDir = _targetPosition - position;
		yaw = YawRotation::GetYawFromDirection(newDir);

		BroadcastManager::Instance()->RegisterBroadcastMove(BroadcastLevel::ALL, gameObject->GetId(), _targetPosition, yaw, Protocol::PLAYER_STATE_MOVE);
	}

	Vector3 targetDirection = (_targetPosition - position).Normalize();

	float moveDistance = speed * deltaTime;
	moveDistance = min(moveDistance, Vector3::Distance(position, _targetPosition));

	position = position + targetDirection * moveDistance;
	World::Instance()->GetNavMesh().GetHeightOnNavMesh(position);
}

void PlayerMoveState::OnExit(FSMComponent<Protocol::PLAYER_STATE>& fsm)
{
	auto gameObject = fsm.GetGameObject().lock();
	if (gameObject == nullptr) return;

	BroadcastManager::Instance()->RegisterBroadcastMove
		(BroadcastLevel::ALL, gameObject->GetId(), fsm.Transform()->Position(), fsm.Transform()->Rotation(), Protocol::PLAYER_STATE_IDLE);

	Log << fsm.Transform()->Position() << endl;
}