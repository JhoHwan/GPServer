#include "pch.h"

#include "ServerPacketHandler.h"
#include "Player.h"
#include "PlayerControllerComponent.h"

using JobRef = shared_ptr<Job>;

PacketHandlerFunc GPacketHandler[UINT16_MAX];

bool Handle_INVALID(SessionRef session, BYTE* buffer, int32 len)
{
    return false;
}

bool Handle_CS_ENTER_GAME(SessionRef session, Protocol::CS_ENTER_GAME& pkt)
{
    shared_ptr<GameServer> server = static_pointer_cast<GameServer>(session->GetServer());
    
    JobRef job = make_shared<Job>([session, server]()
        {
            if (session == nullptr) return;

            auto playerRef = GGameObjectManager()->Instantiate<Player>();
            playerRef.lock()->SetSession(static_pointer_cast<PlayerSession>(session));

            static_pointer_cast<PlayerSession>(session)->SetPlayerRef(playerRef);

            double x, y;
            ObjectId id;

            {
                Protocol::SC_ENTER_GAME pkt;
                pkt.set_success(true);

                auto info = pkt.mutable_player();
                playerRef.lock()->SetObjectInfo(info);

                auto sendBuffer = ServerPacketHandler::MakeSendBuffer(pkt);

                session->Send(sendBuffer);
            }

            {
                Protocol::SC_SPAWN pkt;

                auto players = GGameObjectManager()->FindAllGameObjects<Player>();

                for (auto playerRef : players)
                {
                    auto player = playerRef.lock();
                    auto info = pkt.add_players();
                    player->SetObjectInfo(info);
                }
                auto sendBuffer = ServerPacketHandler::MakeSendBuffer(pkt);

                server->BroadCast(sendBuffer);
            }
        });
    server->InsertJob(job);

    return true;
}

bool Handle_CS_LEAVE_GAME(SessionRef session, Protocol::CS_LEAVE_GAME& pkt)
{
    return false;
}

bool Handle_CS_CHAT(SessionRef session, Protocol::CS_CHAT& pkt)
{
    return false;
}

bool Handle_CS_REQUEST_MOVE(SessionRef session, Protocol::CS_REQUEST_MOVE& pkt)
{
    shared_ptr<GameServer> server = static_pointer_cast<GameServer>(session->GetServer());

    auto id = pkt.playerid();
    Vector2 pos{ pkt.x(), pkt.y() };

    shared_ptr<Job> job = make_shared<Job>([session, id, pos]()
        {
            // ÁÂÇ¥ °Ë»ç
            auto playerRef = GGameObjectManager()->Find(id).lock();
            if (playerRef == nullptr) return;

            playerRef->GetComponent<PlayerControllerComponent>()->RequestMove(pos);
        });

    server->InsertJob(job);
    return true;
}

bool Handle_CS_REQUEST_STOP(SessionRef session, Protocol::CS_REQUEST_STOP& pkt)
{
    shared_ptr<GameServer> server = static_pointer_cast<GameServer>(session->GetServer());

	JobRef job = make_shared<Job>([pkt]()
		{
			auto playerRef = GGameObjectManager()->Find(pkt.playerid()).lock();
			if (playerRef == nullptr) return;
			playerRef->GetComponent<PlayerControllerComponent>()->Stop();
		});

    server->InsertJob(job);

    return true;
}
