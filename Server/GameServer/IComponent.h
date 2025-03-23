#pragma once

class GameObject;

class IComponent
{
protected:
	IComponent(std::weak_ptr<GameObject> owner) : _owner(owner) {}

public:
	virtual ~IComponent() {}

	virtual void Update() = 0;

private:
	std::weak_ptr<GameObject> _owner;
};

