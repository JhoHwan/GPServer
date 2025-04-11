#include "pch.h"

#include "DummyClientPacketHandler.h"
#include "DummySession.h"

PacketHandlerFunc GPacketHandler[UINT16_MAX];

shared_ptr<DummySession> CastSession(SessionRef session)
{
	return static_pointer_cast<DummySession>(session);
}

bool Handle_INVALID(SessionRef session, BYTE* buffer, int32 len)
{
	return false;
}

bool Handle_SC_ENTER_GAME(SessionRef session, Protocol::SC_ENTER_GAME& pkt)
{
	cout << "Enter Game" << endl;
	auto playerInfo = pkt.player();
	playerInfo.objectid();
	return false;
}

bool Handle_SC_LEAVE_GAME(SessionRef session, Protocol::SC_LEAVE_GAME& pkt)
{
	return false;
}

bool Handle_SC_SPAWN(SessionRef session, Protocol::SC_SPAWN& pkt)
{
	cout << "Spawn " << endl;

	
	return false;
}

bool Handle_SC_DESPAWN(SessionRef session, Protocol::SC_DESPAWN& pkt)
{
	return false;
}

bool Handle_SC_CHAT(SessionRef session, Protocol::SC_CHAT& pkt)
{
	return false;
}

bool Handle_SC_BROADCAST_MOVE(SessionRef session, Protocol::SC_BROADCAST_MOVE& pkt)
{
	return false;
}
