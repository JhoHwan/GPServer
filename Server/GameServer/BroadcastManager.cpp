#include "pch.h"
#include "BroadcastManager.h"
#include "Player.h"

void BroadcastManager::TriggerMove(ObjectId id)
{
	_triggerdObjectId.push_back(id);
}

void BroadcastManager::BroadcastAll(float deltaTime)
{
	BroadcastMove(deltaTime);
}

void BroadcastManager::BroadcastMove(float deltaTime)
{
	if (_triggerdObjectId.size() == 0) return;

	for (const auto& playerRef : GGameObjectManager()->GetPlayers())
	{
		auto player = playerRef.lock();
		if (player == nullptr) continue;

		Protocol::SC_BROADCAST_MOVE pkt;

		for(const auto& triggerdId : _triggerdObjectId)
		{ 
			// TODO : Player Ä³½Ì
			auto triggeredPlayerRef = static_pointer_cast<Player>(GGameObjectManager()->Find(triggerdId).lock());
			
			Protocol::ObjectInfo* objInfo = pkt.add_players();
			triggeredPlayerRef->SetObjectInfo(objInfo);

		}
		
		if (pkt.players_size() == 0) continue;

		auto session = player->GetSession().lock();
		if (session == nullptr) continue;

		auto sendBuffer = ServerPacketHandler::MakeSendBuffer(pkt);
		session->Send(sendBuffer);
	}

	_triggerdObjectId.clear();
}
