#pragma once

using GameObjectRef = std::weak_ptr<class GameObject>;

class Component;
class TransformComponent;

template <typename T>
concept ComponentType = std::is_base_of<Component, T>::value;

class GameObject : enable_shared_from_this<GameObject>
{
public:
	GameObject();
	virtual ~GameObject();

	void Update();

public:
	inline ObjectId GetID() const { return _id; }
	inline shared_ptr<TransformComponent> Transform() { return transform; }

	template<ComponentType T>
	std::shared_ptr<T> GetComponent();

	template<ComponentType T, typename... Args>
	std::shared_ptr<T> AddComponent(Args&&... args);

private:
	static class IDGenerator _idGenerator;

	ObjectId _id;
	std::vector<shared_ptr<Component>> _components;

	std::shared_ptr<TransformComponent> transform;

};

template<ComponentType T>
inline shared_ptr<T> GameObject::GetComponent()
{
	for (auto& component : _components)
	{
		auto casted = dynamic_pointer_cast<T>(component);
		if (casted != nullptr)
		{
			return casted;
		}
	}

	return nullptr;
}

template<ComponentType T, typename... Args>
inline shared_ptr<T> GameObject::AddComponent(Args&&... args)
{
	shared_ptr<T> component = make_shared<T>(this, std::forward<Args>(args)...);
	_components.push_back(component);
	return component;
}
