#include "pch.h"
#include "BroadcastManager.h"
#include "Player.h"


void BroadcastManager::RegisterBroadcastMove
(BroadcastLevel level, ObjectId id, const Vector3& position, const YawRotation& yaw, Protocol::PLAYER_STATE state)
{
	if (level == BroadcastLevel::None) return;

	_broadcastInfos.emplace_back(level, id, position, yaw, state);
}

void BroadcastManager::Broadcast(float deltaTime)
{
	BroadcastMove(deltaTime);
}

void BroadcastManager::BroadcastMove(float deltaTime)
{
	if (_broadcastInfos.size() == 0) return;

	for (const auto& playerRef : GGameObjectManager()->GetPlayers())
	{
		auto player = playerRef.lock();
		if (player == nullptr) continue;

		Protocol::SC_BROADCAST_MOVE pkt;

		for (const auto& info : _broadcastInfos)
		{
			// TODO : Player ĳ��
			auto triggeredPlayer = static_pointer_cast<Player>(GGameObjectManager()->Find(info.id).lock());

			if (triggeredPlayer == nullptr) continue;

			Protocol::MoveInfo* moveInfo = pkt.add_objects();
			auto* objInfo = moveInfo->mutable_objectinfo();
			objInfo->set_objectid(triggeredPlayer->GetId());
			objInfo->set_x(info.position.x);
			objInfo->set_y(info.position.y);
			objInfo->set_z(info.position.z);
			objInfo->set_rotate(info.yaw);
			moveInfo->set_state(info.state);
		}

		if (pkt.objects_size() == 0) continue;

		auto session = player->GetSession().lock();
		if (session == nullptr) continue;

		auto sendBuffer = ServerPacketHandler::MakeSendBuffer(pkt);
		session->Send(sendBuffer);
	}

	_broadcastInfos.clear();
}

BroadcastLevel BroadcastManager::CalculateBroadcastLevel(const Vector2& pos1, const Vector2& pos2)
{
	float distance = Vector2::Distance(pos1, pos2);
	if (distance < 80.0f)
	{
		return BroadcastLevel::Level0;
	}
	else if (distance < 1000.0f)
	{
		return BroadcastLevel::Level1;
	}
	else
	{
		return BroadcastLevel::Level2;
	}
}
