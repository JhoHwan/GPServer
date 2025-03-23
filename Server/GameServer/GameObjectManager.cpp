#include "pch.h"
#include "GameObjectManager.h"

void GameObjectManager::Destroy(GameObjectRef gameObject)
{
	if (gameObject.lock() == nullptr) return;

	auto id = gameObject.lock()->GetID();

	auto iter = _gameObjects.find(id);
	if (iter != _gameObjects.end())
	{
		_destroyGameObjectsIds.push_back(id);
	}
}

GameObjectRef GameObjectManager::Find(ObjectId id)
{
	auto iter = _gameObjects.find(id);
	if (iter == _gameObjects.end())
	{
		return GameObjectRef();
	}
	return iter->second;
}

void GameObjectManager::UpdateAll()
{
	for (auto& [id, gameObject] : _gameObjects)
	{
		gameObject->Update();
	}

	for (auto id : _destroyGameObjectsIds)
	{
		_gameObjects.erase(id);
	}

	_destroyGameObjectsIds.clear();
}
