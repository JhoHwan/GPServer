#include "pch.h"
#include "GameObject.h"
#include "GameObjectManager.h"

#include "IComponent.h"

IDGenerator GameObject::_idGenerator{};

GameObject::GameObject() : _id(_idGenerator.GenerateID()), transform(make_shared<TransformComponent>(weak_from_this()))
{
	_components.push_back(transform);
}

GameObject::~GameObject()
{
	_idGenerator.ReleaseID(_id);
	_components.clear();

	cout << "Destroy GameObject : " << _id << endl;
}

void GameObject::Update()
{
	//cout << "Update GameObject : " << _id << endl;

	for (auto& component : _components)
	{
		component->Update();
	}
}
