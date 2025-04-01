#pragma once

using GameObjectRef = std::weak_ptr<class GameObject>;

class Component;
class TransformComponent;

template <typename T>
concept ComponentType = std::is_base_of<Component, T>::value;

class GameObject : public enable_shared_from_this<GameObject>
{
	friend class GameObjectManager;
public:
	GameObject();
	virtual ~GameObject();

	virtual void Init();

	void Update(float deltaTime);

public:
	inline ObjectId GetID() const { return _id; }
	inline std::shared_ptr<TransformComponent>& Transform() { return _transform; }

	template<ComponentType T>
	std::shared_ptr<T> GetComponent();

	template<ComponentType T, typename... Args>
	std::shared_ptr<T> AddComponent(Args&&... args);

	void SetObjectInfo(OUT Protocol::ObjectInfo* const info);

private:
	static class IDGenerator _idGenerator;

	ObjectId _id;
	std::vector<std::shared_ptr<Component>> _components;

	std::shared_ptr<TransformComponent> _transform;

};

template<ComponentType T>
inline shared_ptr<T> GameObject::GetComponent()
{
	for (auto& component : _components)
	{
		auto casted = std::dynamic_pointer_cast<T>(component);
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
	shared_ptr<T> component = make_shared<T>(shared_from_this(), std::forward<Args>(args)...);
	_components.push_back(component);
	return component;
}
