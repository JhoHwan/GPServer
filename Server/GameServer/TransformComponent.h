#pragma once
#include "Component.h"

class TransformComponent : public Component
{
public:
    TransformComponent(std::weak_ptr<GameObject> owner);
	virtual void Update() override {}

public:
	Vector2& Position() { return _position; }

	double& Rotation() { return _rotation; }

	Vector2& Scale() { return _scale; }

private:
	Vector2 _position;
	double _rotation;
	Vector2 _scale;
};
