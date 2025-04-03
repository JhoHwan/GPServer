#pragma once

#include <typeindex>

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
	inline ObjectId GetId() const { return _id; }
	inline std::shared_ptr<TransformComponent>& Transform() { return _transform; }

	template<ComponentType T>
	std::shared_ptr<T> GetComponent();

	template<ComponentType T, typename... Args>
	std::shared_ptr<T> AddComponent(Args&&... args);

	void SetObjectInfo(OUT Protocol::ObjectInfo* const info);

private:
	static class IDGenerator _idGenerator;

	ObjectId _id;
	std::unordered_map<std::type_index, std::shared_ptr<Component>> _components;

	std::shared_ptr<TransformComponent> _transform;

};

template<ComponentType T>
inline shared_ptr<T> GameObject::GetComponent()
{
	if (_components.find(typeid(T)) == _components.end()) return nullptr;
	shared_ptr<T> component = static_pointer_cast<T>(_components[typeid(T)]);

	return component;
}

template<ComponentType T, typename... Args>
inline shared_ptr<T> GameObject::AddComponent(Args&&... args)
{
	if (_components.find(typeid(T)) != _components.end()) return nullptr;

	shared_ptr<T> component = make_shared<T>(shared_from_this(), std::forward<Args>(args)...);
	_components[typeid(T)] = component;
	return component;
}
