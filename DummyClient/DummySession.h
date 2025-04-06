#pragma once

#include "Session.h"

class DummySession : public Session
{
public:
	DummySession() = default;
	~DummySession() override = default;

	void OnRecv(BYTE* buffer, int32 len) override
	{
		auto session = GetSharedPtr();
		PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);

		//ServerPacketHandler::HandlePacket(session, buffer, len);

	}
};