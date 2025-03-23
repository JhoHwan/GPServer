#include "pch.h"

#include "ServerPacketHandler.h"
#include "Player.h"

using JobRef = shared_ptr<Job>;

PacketHandlerFunc GPacketHandler[UINT16_MAX];

bool Handle_INVALID(SessionRef& session, BYTE* buffer, int32 len)
{
    return false;
}

bool Handle_CS_ENTER_GAME(SessionRef& session, Protocol::CS_ENTER_GAME& pkt)
{
    shared_ptr<GameServer> server = static_pointer_cast<GameServer>(session->GetServer());
    
    JobRef job = make_shared<Job>([session, server]()
        {
            if (session == nullptr) return;

            auto playerRef = GGameObjectManager()->Instantiate<Player>();

            static_pointer_cast<PlayerSession>(session)->SetPlayerRef(playerRef);

            double x, y;
            ObjectId id;

            {
                Protocol::SC_ENTER_GAME pkt;
                pkt.set_success(true);

                auto info = pkt.mutable_player();
                playerRef.lock()->SetPlayerInfo(info);

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
                    player->SetPlayerInfo(info);
                }
                auto sendBuffer = ServerPacketHandler::MakeSendBuffer(pkt);

                server->BroadCast(sendBuffer);
            }
        });

    server->InsertJob(job);

    return true;
}

bool Handle_CS_LEAVE_GAME(SessionRef& session, Protocol::CS_LEAVE_GAME& pkt)
{
    return false;
}

bool Handle_CS_CHAT(SessionRef& session, Protocol::CS_CHAT& pkt)
{
    return false;
}

bool Handle_CS_REQUEST_MOVE(SessionRef& session, Protocol::CS_REQUEST_MOVE& pkt)
{
    shared_ptr<GameServer> server = static_pointer_cast<GameServer>(session->GetServer());

    auto id = pkt.objectid();
    uint32 x = pkt.x();
    uint32 y = pkt.y();

    shared_ptr<Job> job = make_shared<Job>([id, x, y]()
        {
            // ÁÂÇ¥ °Ë»ç

            auto playerRef = GGameObjectManager()->Find(id);
            if (playerRef.lock() == nullptr) return;

        });

    server->InsertJob(job);
    return true;
}
