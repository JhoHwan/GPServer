#pragma once

#pragma comment(lib, "ServerLib.lib")

#pragma comment(lib, "Detour.lib")
#pragma comment(lib, "DetourCrowd.lib")

using ObjectId = uint32;

#include "Vector2.h"
#include "IDGenerator.h"
//#include "Packet.h"
#include "PlayerSession.h"
#include "GameServer.h"
#include "ServerPacketHandler.h"

#include "GameObject.h"
#include "TransformComponent.h"
#include "DoubleJobQueue.h"

#include "GameObjectManager.h"
#include "BroadcastManager.h"
#include "LogManager.h"
#include "AStarManager.h"