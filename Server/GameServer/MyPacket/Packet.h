#pragma once
///////////////////////////////
/////// AUTO-GENERATING ///////
///////////////////////////////

enum class PacketType : uint16
{
    GC_SendPlayerInfo,
	GC_CheckKeepAlive,
	CG_ResponseKeepAlive,
	CG_RequestEnterRoom,
	GC_ResponseEnterRoom,
	GC_ExitPlayerRoom,
	CG_PlayerReady,
	GC_ResponsePlayerReady,
	GC_BroadCastGameStart,
	CG_SendDonglePool,
	GC_BroadCastDonglePool,
	CG_MergeDongle,
	GC_BroadCastMergeDongle,
	GC_BroadCastGameOver,
	
	INVALID_PACKET,
};

class GC_SendPlayerInfo : public IPacket
{
public:
	//���� ����
	uint8 playerID;
	
	//���ڿ�
	
	//����Ʈ
	
public:
	uint16 GetDataSize() const override
	{
		size_t size = sizeof(PacketHeader);

		//���� ���� size
		size = size + sizeof(playerID);
		//���ڿ� size
		
		//����Ʈ size
		
		return static_cast<uint16>(size);
	}

	bool Serialize(BYTE* buffer) const override
	{
		PacketHeader header;
		header.packetType = PacketType::GC_SendPlayerInfo;
		header.packetSize = GetDataSize();

		PacketWriter pw(buffer);
		pw << header << playerID;
		
		return pw.GetSize() == GetDataSize();
	}

	bool Deserialize(BYTE* buffer) override
	{
		PacketReader pr(buffer);

		PacketHeader header;
		pr >> header >> playerID;

		return GetDataSize() == header.packetSize;
	}
};

class GC_CheckKeepAlive : public IPacket
{
public:
	//���� ����
	uint8 playerID;
	
	//���ڿ�
	
	//����Ʈ
	
public:
	uint16 GetDataSize() const override
	{
		size_t size = sizeof(PacketHeader);

		//���� ���� size
		size = size + sizeof(playerID);
		//���ڿ� size
		
		//����Ʈ size
		
		return static_cast<uint16>(size);
	}

	bool Serialize(BYTE* buffer) const override
	{
		PacketHeader header;
		header.packetType = PacketType::GC_CheckKeepAlive;
		header.packetSize = GetDataSize();

		PacketWriter pw(buffer);
		pw << header << playerID;
		
		return pw.GetSize() == GetDataSize();
	}

	bool Deserialize(BYTE* buffer) override
	{
		PacketReader pr(buffer);

		PacketHeader header;
		pr >> header >> playerID;

		return GetDataSize() == header.packetSize;
	}
};

class CG_ResponseKeepAlive : public IPacket
{
public:
	//���� ����
	uint8 playerID;
	
	//���ڿ�
	
	//����Ʈ
	
public:
	uint16 GetDataSize() const override
	{
		size_t size = sizeof(PacketHeader);

		//���� ���� size
		size = size + sizeof(playerID);
		//���ڿ� size
		
		//����Ʈ size
		
		return static_cast<uint16>(size);
	}

	bool Serialize(BYTE* buffer) const override
	{
		PacketHeader header;
		header.packetType = PacketType::CG_ResponseKeepAlive;
		header.packetSize = GetDataSize();

		PacketWriter pw(buffer);
		pw << header << playerID;
		
		return pw.GetSize() == GetDataSize();
	}

	bool Deserialize(BYTE* buffer) override
	{
		PacketReader pr(buffer);

		PacketHeader header;
		pr >> header >> playerID;

		return GetDataSize() == header.packetSize;
	}
};

class CG_RequestEnterRoom : public IPacket
{
public:
	//���� ����
	uint16 playerID;
	uint16 roomID;
	
	//���ڿ�
	
	//����Ʈ
	
public:
	uint16 GetDataSize() const override
	{
		size_t size = sizeof(PacketHeader);

		//���� ���� size
		size = size + sizeof(playerID)+ sizeof(roomID);
		//���ڿ� size
		
		//����Ʈ size
		
		return static_cast<uint16>(size);
	}

	bool Serialize(BYTE* buffer) const override
	{
		PacketHeader header;
		header.packetType = PacketType::CG_RequestEnterRoom;
		header.packetSize = GetDataSize();

		PacketWriter pw(buffer);
		pw << header << playerID << roomID;
		
		return pw.GetSize() == GetDataSize();
	}

	bool Deserialize(BYTE* buffer) override
	{
		PacketReader pr(buffer);

		PacketHeader header;
		pr >> header >> playerID >> roomID;

		return GetDataSize() == header.packetSize;
	}
};

class GC_ResponseEnterRoom : public IPacket
{
public:
	//���� ����
	uint16 playerID;
	uint16 roomID;
	uint8 bSuccess;
	RoomInfo roomInfo;
	
	//���ڿ�
	
	//����Ʈ
	vector<uint16> playerList;
	
public:
	uint16 GetDataSize() const override
	{
		size_t size = sizeof(PacketHeader);

		//���� ���� size
		size = size + sizeof(playerID)+ sizeof(roomID)+ sizeof(bSuccess)+ sizeof(roomInfo);
		//���ڿ� size
		
		//����Ʈ size
		size += sizeof(uint16);
		size += playerList.size() * sizeof(uint16);
		
		return static_cast<uint16>(size);
	}

	bool Serialize(BYTE* buffer) const override
	{
		PacketHeader header;
		header.packetType = PacketType::GC_ResponseEnterRoom;
		header.packetSize = GetDataSize();

		PacketWriter pw(buffer);
		pw << header << playerID << roomID << bSuccess << roomInfo << playerList;
		
		return pw.GetSize() == GetDataSize();
	}

	bool Deserialize(BYTE* buffer) override
	{
		PacketReader pr(buffer);

		PacketHeader header;
		pr >> header >> playerID >> roomID >> bSuccess >> roomInfo >> playerList;

		return GetDataSize() == header.packetSize;
	}
};

class GC_ExitPlayerRoom : public IPacket
{
public:
	//���� ����
	uint8 playerID;
	
	//���ڿ�
	
	//����Ʈ
	
public:
	uint16 GetDataSize() const override
	{
		size_t size = sizeof(PacketHeader);

		//���� ���� size
		size = size + sizeof(playerID);
		//���ڿ� size
		
		//����Ʈ size
		
		return static_cast<uint16>(size);
	}

	bool Serialize(BYTE* buffer) const override
	{
		PacketHeader header;
		header.packetType = PacketType::GC_ExitPlayerRoom;
		header.packetSize = GetDataSize();

		PacketWriter pw(buffer);
		pw << header << playerID;
		
		return pw.GetSize() == GetDataSize();
	}

	bool Deserialize(BYTE* buffer) override
	{
		PacketReader pr(buffer);

		PacketHeader header;
		pr >> header >> playerID;

		return GetDataSize() == header.packetSize;
	}
};

class CG_PlayerReady : public IPacket
{
public:
	//���� ����
	uint16 roomID;
	uint16 playerID;
	
	//���ڿ�
	
	//����Ʈ
	
public:
	uint16 GetDataSize() const override
	{
		size_t size = sizeof(PacketHeader);

		//���� ���� size
		size = size + sizeof(roomID)+ sizeof(playerID);
		//���ڿ� size
		
		//����Ʈ size
		
		return static_cast<uint16>(size);
	}

	bool Serialize(BYTE* buffer) const override
	{
		PacketHeader header;
		header.packetType = PacketType::CG_PlayerReady;
		header.packetSize = GetDataSize();

		PacketWriter pw(buffer);
		pw << header << roomID << playerID;
		
		return pw.GetSize() == GetDataSize();
	}

	bool Deserialize(BYTE* buffer) override
	{
		PacketReader pr(buffer);

		PacketHeader header;
		pr >> header >> roomID >> playerID;

		return GetDataSize() == header.packetSize;
	}
};

class GC_ResponsePlayerReady : public IPacket
{
public:
	//���� ����
	uint16 playerID;
	
	//���ڿ�
	
	//����Ʈ
	
public:
	uint16 GetDataSize() const override
	{
		size_t size = sizeof(PacketHeader);

		//���� ���� size
		size = size + sizeof(playerID);
		//���ڿ� size
		
		//����Ʈ size
		
		return static_cast<uint16>(size);
	}

	bool Serialize(BYTE* buffer) const override
	{
		PacketHeader header;
		header.packetType = PacketType::GC_ResponsePlayerReady;
		header.packetSize = GetDataSize();

		PacketWriter pw(buffer);
		pw << header << playerID;
		
		return pw.GetSize() == GetDataSize();
	}

	bool Deserialize(BYTE* buffer) override
	{
		PacketReader pr(buffer);

		PacketHeader header;
		pr >> header >> playerID;

		return GetDataSize() == header.packetSize;
	}
};

class GC_BroadCastGameStart : public IPacket
{
public:
	//���� ����
	uint16 playerID;
	
	//���ڿ�
	
	//����Ʈ
	
public:
	uint16 GetDataSize() const override
	{
		size_t size = sizeof(PacketHeader);

		//���� ���� size
		size = size + sizeof(playerID);
		//���ڿ� size
		
		//����Ʈ size
		
		return static_cast<uint16>(size);
	}

	bool Serialize(BYTE* buffer) const override
	{
		PacketHeader header;
		header.packetType = PacketType::GC_BroadCastGameStart;
		header.packetSize = GetDataSize();

		PacketWriter pw(buffer);
		pw << header << playerID;
		
		return pw.GetSize() == GetDataSize();
	}

	bool Deserialize(BYTE* buffer) override
	{
		PacketReader pr(buffer);

		PacketHeader header;
		pr >> header >> playerID;

		return GetDataSize() == header.packetSize;
	}
};

class CG_SendDonglePool : public IPacket
{
public:
	//���� ����
	uint16 playerID;
	uint16 roomID;
	
	//���ڿ�
	
	//����Ʈ
	vector<DongleInfo> dongleInfos;
	
public:
	uint16 GetDataSize() const override
	{
		size_t size = sizeof(PacketHeader);

		//���� ���� size
		size = size + sizeof(playerID)+ sizeof(roomID);
		//���ڿ� size
		
		//����Ʈ size
		size += sizeof(uint16);
		size += dongleInfos.size() * sizeof(DongleInfo);
		
		return static_cast<uint16>(size);
	}

	bool Serialize(BYTE* buffer) const override
	{
		PacketHeader header;
		header.packetType = PacketType::CG_SendDonglePool;
		header.packetSize = GetDataSize();

		PacketWriter pw(buffer);
		pw << header << playerID << roomID << dongleInfos;
		
		return pw.GetSize() == GetDataSize();
	}

	bool Deserialize(BYTE* buffer) override
	{
		PacketReader pr(buffer);

		PacketHeader header;
		pr >> header >> playerID >> roomID >> dongleInfos;

		return GetDataSize() == header.packetSize;
	}
};

class GC_BroadCastDonglePool : public IPacket
{
public:
	//���� ����
	uint16 playerID;
	
	//���ڿ�
	
	//����Ʈ
	vector<DongleInfo> dongleInfos;
	
public:
	uint16 GetDataSize() const override
	{
		size_t size = sizeof(PacketHeader);

		//���� ���� size
		size = size + sizeof(playerID);
		//���ڿ� size
		
		//����Ʈ size
		size += sizeof(uint16);
		size += dongleInfos.size() * sizeof(DongleInfo);
		
		return static_cast<uint16>(size);
	}

	bool Serialize(BYTE* buffer) const override
	{
		PacketHeader header;
		header.packetType = PacketType::GC_BroadCastDonglePool;
		header.packetSize = GetDataSize();

		PacketWriter pw(buffer);
		pw << header << playerID << dongleInfos;
		
		return pw.GetSize() == GetDataSize();
	}

	bool Deserialize(BYTE* buffer) override
	{
		PacketReader pr(buffer);

		PacketHeader header;
		pr >> header >> playerID >> dongleInfos;

		return GetDataSize() == header.packetSize;
	}
};

class CG_MergeDongle : public IPacket
{
public:
	//���� ����
	uint16 playerID;
	uint16 roomID;
	uint16 dongleID;
	
	//���ڿ�
	
	//����Ʈ
	
public:
	uint16 GetDataSize() const override
	{
		size_t size = sizeof(PacketHeader);

		//���� ���� size
		size = size + sizeof(playerID)+ sizeof(roomID)+ sizeof(dongleID);
		//���ڿ� size
		
		//����Ʈ size
		
		return static_cast<uint16>(size);
	}

	bool Serialize(BYTE* buffer) const override
	{
		PacketHeader header;
		header.packetType = PacketType::CG_MergeDongle;
		header.packetSize = GetDataSize();

		PacketWriter pw(buffer);
		pw << header << playerID << roomID << dongleID;
		
		return pw.GetSize() == GetDataSize();
	}

	bool Deserialize(BYTE* buffer) override
	{
		PacketReader pr(buffer);

		PacketHeader header;
		pr >> header >> playerID >> roomID >> dongleID;

		return GetDataSize() == header.packetSize;
	}
};

class GC_BroadCastMergeDongle : public IPacket
{
public:
	//���� ����
	uint16 playerID;
	uint16 dongleID;
	
	//���ڿ�
	
	//����Ʈ
	
public:
	uint16 GetDataSize() const override
	{
		size_t size = sizeof(PacketHeader);

		//���� ���� size
		size = size + sizeof(playerID)+ sizeof(dongleID);
		//���ڿ� size
		
		//����Ʈ size
		
		return static_cast<uint16>(size);
	}

	bool Serialize(BYTE* buffer) const override
	{
		PacketHeader header;
		header.packetType = PacketType::GC_BroadCastMergeDongle;
		header.packetSize = GetDataSize();

		PacketWriter pw(buffer);
		pw << header << playerID << dongleID;
		
		return pw.GetSize() == GetDataSize();
	}

	bool Deserialize(BYTE* buffer) override
	{
		PacketReader pr(buffer);

		PacketHeader header;
		pr >> header >> playerID >> dongleID;

		return GetDataSize() == header.packetSize;
	}
};

class GC_BroadCastGameOver : public IPacket
{
public:
	//���� ����
	
	//���ڿ�
	
	//����Ʈ
	
public:
	uint16 GetDataSize() const override
	{
		size_t size = sizeof(PacketHeader);

		//���� ���� size
		size = size ;
		//���ڿ� size
		
		//����Ʈ size
		
		return static_cast<uint16>(size);
	}

	bool Serialize(BYTE* buffer) const override
	{
		PacketHeader header;
		header.packetType = PacketType::GC_BroadCastGameOver;
		header.packetSize = GetDataSize();

		PacketWriter pw(buffer);
		pw << header;
		
		return pw.GetSize() == GetDataSize();
	}

	bool Deserialize(BYTE* buffer) override
	{
		PacketReader pr(buffer);

		PacketHeader header;
		pr >> header;

		return GetDataSize() == header.packetSize;
	}
};
