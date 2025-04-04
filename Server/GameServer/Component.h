#pragma once

class GameObject;

class Component
{
protected:
	Component(std::weak_ptr<GameObject> owner) : _owner(owner) {}

public:
	virtual ~Component() {}

	virtual void Update(float deltaTime) = 0;

	inline std::weak_ptr<GameObject> GetGameObject() { return _owner; }
	inline std::shared_ptr<TransformComponent> Transform()
	{
		auto gameObject = _owner.lock();
		if (gameObject == nullptr) return nullptr;
		return gameObject->Transform();
	}

private:
	std::weak_ptr<GameObject> _owner;
};

