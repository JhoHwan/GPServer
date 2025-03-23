#if 0

#pragma once
///////////////////////////////
/////// AUTO-GENERATING ///////
///////////////////////////////

using PacketDispatcher = std::function<void(BYTE*)>;

class ServerPacketHandler : public PacketHandler
{
public:
	ServerPacketHandler()
	{
		for (int i = 0; i < _packetDispatchers.size(); i++)
		{
			_packetDispatchers[i] = std::bind(&ServerPacketHandler::DispatchInvalidPacket, this);
		}
		
		_packetDispatchers[static_cast<uint16>(PacketType::CG_ResponseKeepAlive)] = std::bind(&ServerPacketHandler::Dispatch_CG_ResponseKeepAlive, this, placeholders::_1);
		_packetDispatchers[static_cast<uint16>(PacketType::CG_RequestEnterRoom)] = std::bind(&ServerPacketHandler::Dispatch_CG_RequestEnterRoom, this, placeholders::_1);
		_packetDispatchers[static_cast<uint16>(PacketType::CG_PlayerReady)] = std::bind(&ServerPacketHandler::Dispatch_CG_PlayerReady, this, placeholders::_1);
		_packetDispatchers[static_cast<uint16>(PacketType::CG_SendDonglePool)] = std::bind(&ServerPacketHandler::Dispatch_CG_SendDonglePool, this, placeholders::_1);
		_packetDispatchers[static_cast<uint16>(PacketType::CG_MergeDongle)] = std::bind(&ServerPacketHandler::Dispatch_CG_MergeDongle, this, placeholders::_1);

	}
	~ServerPacketHandler() {}

// PacketDispatcher
public:
	void Dispatch_CG_ResponseKeepAlive(BYTE* buffer);
	void Dispatch_CG_RequestEnterRoom(BYTE* buffer);
	void Dispatch_CG_PlayerReady(BYTE* buffer);
	void Dispatch_CG_SendDonglePool(BYTE* buffer);
	void Dispatch_CG_MergeDongle(BYTE* buffer);
	

public:
	static shared_ptr<SendBuffer> Send_GC_SendPlayerInfo(GC_SendPlayerInfo& packet);
	static shared_ptr<SendBuffer> Send_GC_CheckKeepAlive(GC_CheckKeepAlive& packet);
	static shared_ptr<SendBuffer> Send_GC_ResponseEnterRoom(GC_ResponseEnterRoom& packet);
	static shared_ptr<SendBuffer> Send_GC_ExitPlayerRoom(GC_ExitPlayerRoom& packet);
	static shared_ptr<SendBuffer> Send_GC_ResponsePlayerReady(GC_ResponsePlayerReady& packet);
	static shared_ptr<SendBuffer> Send_GC_BroadCastGameStart(GC_BroadCastGameStart& packet);
	static shared_ptr<SendBuffer> Send_GC_BroadCastDonglePool(GC_BroadCastDonglePool& packet);
	static shared_ptr<SendBuffer> Send_GC_BroadCastMergeDongle(GC_BroadCastMergeDongle& packet);
	static shared_ptr<SendBuffer> Send_GC_BroadCastGameOver(GC_BroadCastGameOver& packet);
	

// PacketHandler을(를) 통해 상속됨
public:
	bool ReadPacket(RecvBuffer& recvBuffer, OUT uint32& packetSize) override;
	bool ProcessPacket(BYTE* packet) override;

private:
	array<PacketDispatcher, UINT16_MAX> _packetDispatchers;
};
#endif