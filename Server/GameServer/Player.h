#pragma once
#include "GameObject.h"

using PlayerRef = std::weak_ptr<class Player>;

class Player : public GameObject
{
public:
	Player();
	virtual ~Player();

	virtual void Init() override;

public:
	inline void SetSession(std::weak_ptr<class PlayerSession> sessionRef) { _sessionRef = sessionRef; }
	inline std::weak_ptr<class PlayerSession> GetSession() { return _sessionRef; }

private:
	std::weak_ptr<class PlayerSession> _sessionRef;
};
