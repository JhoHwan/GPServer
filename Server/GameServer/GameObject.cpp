#include "pch.h"
#include "GameObject.h"
#include "GameObjectManager.h"

#include "Component.h"
#include <format>

IDGenerator GameObject::_idGenerator{};

GameObject::GameObject() : _id(_idGenerator.GenerateID())
{
}

GameObject::~GameObject()
{
	_idGenerator.ReleaseID(_id);
	_components.clear();

	Log << "Destroy GameObject : " << _id << endl;
}

void GameObject::Update(float deltaTime)
{
	//cout << "Update GameObject : " << _id << endl;

	for (auto& [type, component] : _components)
	{
		component->Update(deltaTime);
	}
}

void GameObject::SetObjectInfo(OUT Protocol::ObjectInfo* const info)
{
	info->set_x(Transform()->Position().x);
	info->set_y(Transform()->Position().y);
	info->set_objectid(GetId());
}

void GameObject::Init()
{
	_transform = AddComponent<TransformComponent>();
}
