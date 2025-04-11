#pragma once
#include "Component.h"

class TransformComponent : public Component
{
public:
    TransformComponent(std::weak_ptr<GameObject> owner);
	virtual void Update(float deltaTime) override {}

public:
	Vector3& Position() { return _position; }

	YawRotation& Rotation() { return _rotation; }

	Vector3& Scale() { return _scale; }

private:
	Vector3 _position;
	YawRotation _rotation;
	Vector3 _scale;
};
