#include "pch.h"
#include "GameObjectManager.h"
#include "Player.h"

void GameObjectManager::Destroy(GameObjectRef gameObject)
{
	if (gameObject.lock() == nullptr) return;

	auto id = gameObject.lock()->GetId();

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

void GameObjectManager::UpdateAll(float deltaTime)
{
	for (auto& [id, gameObject] : _gameObjects)
	{
		gameObject->Update(deltaTime);
	}

	for (auto id : _destroyGameObjectsIds)
	{
		_gameObjects.erase(id);
	}

	_destroyGameObjectsIds.clear();
}

void GameObjectManager::AddPlayer(weak_ptr<Player> ref)
{
	_playerRefs.emplace_back(ref);
}

vector<weak_ptr<class Player>>& GameObjectManager::GetPlayers()
{
	return _playerRefs;
}

