#include "pch.h"

#include "PlayerSession.h"
#include "GameServer.h"
#include "Player.h"

PlayerSession::PlayerSession() : Session()
{
}

PlayerSession::~PlayerSession()
{

}

void PlayerSession::OnConnected()
{
	Session::OnConnected();


}

void PlayerSession::OnDisconnected()
{
	Session::OnDisconnected();

	shared_ptr<Job> job = make_shared<Job>([playerRef = _playerRef]()
		{
			GGameObjectManager()->Destroy(playerRef);
		});

	static_pointer_cast<GameServer>(GetServer())->InsertJob(job);
}

void PlayerSession::OnSend(uint32 sentBytes)
{
	
}

void PlayerSession::OnRecv(BYTE* buffer, int32 len)
{
	auto session = GetSharedPtr();
	PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);

	ServerPacketHandler::HandlePacket(session, buffer, len);
}
