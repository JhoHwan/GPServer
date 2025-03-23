#include "pch.h"

#include "ServerPacketHandler.h"

bool ServerPacketHandler::ReadPacket(RecvBuffer& recvBuffer, OUT uint32& packetSize)
{
    if (recvBuffer.DataSize() < sizeof(PacketHeader)) return false;

    BYTE* buffer = recvBuffer.ReadPos();
    PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);

    if (header->packetSize > recvBuffer.DataSize())
    {
        return false;
    }

    packetSize = header->packetSize;

    //cout << "Recv Packet : " << packetSize << endl;

    return true;
}

bool ServerPacketHandler::ProcessPacket(BYTE* packet)
{
    PacketHeader* header = reinterpret_cast<PacketHeader*>(packet);
    PacketType type = header->packetType;

    _packetDispatchers[static_cast<uint16>(type)](packet);

    return true;
}

void ServerPacketHandler::Dispatch_CG_ResponseKeepAlive(BYTE* buffer)
{
}

void ServerPacketHandler::Dispatch_CG_RequestEnterRoom(BYTE* buffer)
{
    CG_RequestEnterRoom packet;
    packet.Deserialize(buffer);
    auto player = static_pointer_cast<GameServer>(_owner)->GetPlayer(packet.playerID);
    if (player == nullptr) return;


    auto room = GRoomManager.GetRoom(packet.roomID);

    if (room == nullptr)
    {
        GC_ResponseEnterRoom packet;
        packet.bSuccess = 0;
        auto sendBuffer = Send_GC_ResponseEnterRoom(packet);
        player->Send(sendBuffer);
        return;
    }

    shared_ptr<Job> job = make_shared<Job>(&Room::EnterPlayer, room, player);
    room->PushJob(job);
}

void ServerPacketHandler::Dispatch_CG_PlayerReady(BYTE* buffer)
{
    CG_PlayerReady rp;
    rp.Deserialize(buffer);
    auto room = GRoomManager.GetRoom(rp.roomID);

    shared_ptr<Job> job = make_shared<Job>([rp, room]()
    {
        room->PlayerReady(rp.playerID);
    });

    room->PushJob(job);
}

void ServerPacketHandler::Dispatch_CG_SendDonglePool(BYTE* buffer)
{
    CG_SendDonglePool rp;
    rp.Deserialize(buffer);
    auto room = GRoomManager.GetRoom(rp.roomID);

    shared_ptr<Job> job = make_shared<Job>([rp, room]()
    {
        GC_BroadCastDonglePool sp;
        sp.playerID = rp.playerID;
        sp.dongleInfos = rp.dongleInfos;

        room->BroadCast(Send_GC_BroadCastDonglePool(sp));
    });
    room->PushJob(job);
}

void ServerPacketHandler::Dispatch_CG_MergeDongle(BYTE* buffer)
{
    CG_MergeDongle rp;
    rp.Deserialize(buffer);
    auto room = GRoomManager.GetRoom(rp.roomID);
    
    shared_ptr<Job> job = make_shared<Job>([rp, room]()
    {
        GC_BroadCastMergeDongle sp;
        sp.dongleID = rp.dongleID;
        sp.playerID = rp.playerID;
        auto buf = Send_GC_BroadCastMergeDongle(sp);
        room->BroadCast(buf);
    });

    room->PushJob(job);
}

shared_ptr<SendBuffer> ServerPacketHandler::Send_GC_SendPlayerInfo(GC_SendPlayerInfo& packet)
{
	shared_ptr<SendBuffer> sendBuffer = make_shared<SendBuffer>(packet.GetDataSize());
    packet.Serialize(sendBuffer->Buffer());
    return sendBuffer;
}

std::shared_ptr<SendBuffer> ServerPacketHandler::Send_GC_CheckKeepAlive(GC_CheckKeepAlive& packet)
{
    shared_ptr<SendBuffer> sendBuffer = make_shared<SendBuffer>(packet.GetDataSize());
    packet.Serialize(sendBuffer->Buffer());
    return sendBuffer;
}

shared_ptr<SendBuffer> ServerPacketHandler::Send_GC_ResponseEnterRoom(GC_ResponseEnterRoom& packet)
{
    shared_ptr<SendBuffer> sendBuffer = make_shared<SendBuffer>(packet.GetDataSize());
    packet.Serialize(sendBuffer->Buffer());
    return sendBuffer;
}

shared_ptr<SendBuffer> ServerPacketHandler::Send_GC_ExitPlayerRoom(GC_ExitPlayerRoom& packet)
{
    shared_ptr<SendBuffer> sendBuffer = make_shared<SendBuffer>(packet.GetDataSize());
    packet.Serialize(sendBuffer->Buffer());
    return sendBuffer;
}

shared_ptr<SendBuffer> ServerPacketHandler::Send_GC_BroadCastDonglePool(GC_BroadCastDonglePool& packet)
{
    shared_ptr<SendBuffer> sendBuffer = make_shared<SendBuffer>(packet.GetDataSize());
    packet.Serialize(sendBuffer->Buffer());
    return sendBuffer;
}

shared_ptr<SendBuffer> ServerPacketHandler::Send_GC_ResponsePlayerReady(GC_ResponsePlayerReady& packet)
{
    shared_ptr<SendBuffer> sendBuffer = make_shared<SendBuffer>(packet.GetDataSize());
    packet.Serialize(sendBuffer->Buffer());
    return sendBuffer;
}

shared_ptr<SendBuffer> ServerPacketHandler::Send_GC_BroadCastGameStart(GC_BroadCastGameStart& packet)
{
    shared_ptr<SendBuffer> sendBuffer = make_shared<SendBuffer>(packet.GetDataSize());
    packet.Serialize(sendBuffer->Buffer());
    return sendBuffer;
}

shared_ptr<SendBuffer> ServerPacketHandler::Send_GC_BroadCastMergeDongle(GC_BroadCastMergeDongle& packet)
{
    shared_ptr<SendBuffer> sendBuffer = make_shared<SendBuffer>(packet.GetDataSize());
    packet.Serialize(sendBuffer->Buffer());
    return sendBuffer;
}

shared_ptr<SendBuffer> ServerPacketHandler::Send_GC_BroadCastGameOver(GC_BroadCastGameOver& packet)
{
    shared_ptr<SendBuffer> sendBuffer = make_shared<SendBuffer>(packet.GetDataSize());
    packet.Serialize(sendBuffer->Buffer());
    return sendBuffer;
}
