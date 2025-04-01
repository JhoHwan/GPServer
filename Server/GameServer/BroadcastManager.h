#pragma once

#include "Singleton.h"

class BroadcastManager : public Singleton<BroadcastManager>
{
	friend Singleton<BroadcastManager>;

private:
	BroadcastManager() = default;

public:
	void TriggerMove(ObjectId id);

	void BroadcastAll(float deltaTime);

private:
	void BroadcastMove(float deltaTime);

private:
	std::vector<ObjectId> _triggerdObjectId;
};