#pragma once

class GameObject;

class Component
{
protected:
	Component(std::weak_ptr<GameObject> owner) : _owner(owner) {}

public:
	virtual ~Component() {}

	virtual void Update() = 0;

	inline std::weak_ptr<GameObject> GetGameObject() { return _owner; }

private:
	std::weak_ptr<GameObject> _owner;
};

