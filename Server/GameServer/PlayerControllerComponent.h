#pragma once
#include "Component.h"

class Player;

class PlayerControllerComponent : public Component
{
public:
	PlayerControllerComponent(std::weak_ptr<GameObject> owner);

	void Update(float deltaTime) override;

public:
	bool IsValidPosition();
	void MoveTo(const Vector2& goal);

public:
	inline bool IsMoving() const { return _isMoving; }

private:
	void FindPaths(OUT vector<Vector2> outPaths, const Vector2& start, const Vector2& goal);


private:
	bool _isMoving;

	Vector2 _goal;
	vector<Vector2> _paths;
};

