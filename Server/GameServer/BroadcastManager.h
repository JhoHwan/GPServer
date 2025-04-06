#pragma once

#include "Singleton.h"

enum BroadcastLevel
{
	Level0 = 0, // 자기 자신 + 근거리
	Level1, // Level0 + 중거리
	Level2, // Level1 + 원거리
	ALL, // 모든 클라이언트
	None,
};

struct BroadcastInfo
{
	BroadcastLevel level = BroadcastLevel::None;
	ObjectId id = 0;
	Vector2 position = Vector2::Zero();
	Protocol::PLAYER_STATE state = Protocol::PLAYER_STATE::PLAYER_STATE_NONE;
};

class BroadcastManager : public Singleton<BroadcastManager>
{
	friend Singleton<BroadcastManager>;

private:
	BroadcastManager() = default;

public:
	void RegisterBroadcastMove(BroadcastLevel level, ObjectId id, Vector2 position, Protocol::PLAYER_STATE state);

	void Broadcast(float deltaTime);

private:
	void BroadcastMove(float deltaTime);

	BroadcastLevel CalculateBroadcastLevel(const Vector2& pos1, const Vector2& pos2);

private:
	std::vector<BroadcastInfo> _broadcastInfos;
};