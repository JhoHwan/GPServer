#include "pch.h"
#include "BroadcastManager.h"
#include "Player.h"


void BroadcastManager::RegisterBroadcastMove(BroadcastLevel level, ObjectId id, Vector2 position, Protocol::PLAYER_STATE state)
{
	if (level == BroadcastLevel::None) return;

	_broadcastInfos.emplace_back(level, id, position, state);
}

void BroadcastManager::BroadcastAll(float deltaTime)
{
	BroadcastMove(deltaTime);
}

void BroadcastManager::BroadcastMove(float deltaTime)
{
	static float startTime = 0;
	static uint32 sendPacketCount = 0;
	startTime += deltaTime;

	if (startTime >= 1.0f)
	{
		startTime = 0;
		//Log << "Broadcast Count : " << sendPacketCount << endl;
		sendPacketCount = 0;
	}

	if (_broadcastInfos.size() == 0) return;

	for (const auto& playerRef : GGameObjectManager()->GetPlayers())
	{
		auto player = playerRef.lock();
		if (player == nullptr) continue;

		Protocol::SC_BROADCAST_MOVE pkt;

		for (const auto& info : _broadcastInfos)
		{
			// TODO : Player Ä³½Ì
			auto triggeredPlayer = static_pointer_cast<Player>(GGameObjectManager()->Find(info.id).lock());

			if (triggeredPlayer->GetId() == player->GetId())
			{
				Protocol::MoveInfo* moveInfo = pkt.add_objects();
				triggeredPlayer->SetObjectInfo(moveInfo->mutable_objectinfo());
				moveInfo->set_state(info.state);
				continue;
			}

			auto broadcastLevel = CalculateBroadcastLevel(player->Transform()->Position(), info.position);
			if (broadcastLevel > info.level) continue;
		
			Protocol::MoveInfo* moveInfo = pkt.add_objects();
			triggeredPlayer->SetObjectInfo(moveInfo->mutable_objectinfo());
			moveInfo->set_state(info.state);
	
		}

		if (pkt.objects_size() == 0) continue;

		auto session = player->GetSession().lock();
		if (session == nullptr) continue;

		auto sendBuffer = ServerPacketHandler::MakeSendBuffer(pkt);
		session->Send(sendBuffer);
		sendPacketCount++;
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
