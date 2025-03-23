#pragma once
#include "GameObject.h"

using PlayerRef = std::weak_ptr<class Player>;

class Player : public GameObject
{
public:
	virtual ~Player();
	
	void SetPlayerInfo(OUT Protocol::PlayerInfo* const info);
};
