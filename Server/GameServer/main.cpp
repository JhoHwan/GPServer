#include "pch.h"

#include <functional>
#include <random>

#include "Player.h"
#include "World.h"
#include "GameServer.h"
#include "GameObjectManager.h"
#include "PlayerControllerComponent.h"
#include "ServerPacketHandler.h"
#include "NavgationAgentCompnent.h"

using Time = std::chrono::high_resolution_clock;

int main()
{
	ServerPacketHandler::Init();

	NetAddress addr(L"127.0.0.1", 7777);
	shared_ptr<GameServer> server
		= std::make_shared<GameServer>(addr, make_shared<PlayerSession>);

	server->Start();

	server->GameLoop(33ms);

	server->Stop();
}