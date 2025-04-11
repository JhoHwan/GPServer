#pragma once

#include "Session.h"
#include "DummyClientPacketHandler.h"

class DummySession : public Session
{
public:
	DummySession() = default;
	~DummySession() override = default;

	void OnConnected() override
	{
		Session::OnConnected();
		Protocol::CS_ENTER_GAME pkt;
		auto sendPacket = DummyClientPacketHandler::MakeSendBuffer(pkt);
		Send(sendPacket);
	}

	void OnSend(uint32 sentBytes) override
	{
		wprintf(L"Send : %d\n", sentBytes);
	}

	void OnRecv(BYTE* buffer, int32 len) override
	{
		Session::OnRecv(buffer, len);
		auto session = GetSharedPtr();
		PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);

		DummyClientPacketHandler::HandlePacket(session, buffer, len);

	}
};