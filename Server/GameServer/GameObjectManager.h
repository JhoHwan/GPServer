#pragma once

#include "Singleton.h"

template <typename T>
concept GameObjectType = std::is_base_of<GameObject, T>::value;

class GameObjectManager : public Singleton<GameObjectManager>
{
	friend class Singleton<GameObjectManager>;

private:
	GameObjectManager() = default;

public:
	// GameObject 생성
	template<GameObjectType T, typename... Args>
	std::weak_ptr<T> Instantiate(Args&&... args);

	// GameObject 생성
	template<GameObjectType T, typename... Args>
	std::weak_ptr<T> Instantiate(Vector2 pos, Args&&... args);

	// GameObject 삭제
	void Destroy(GameObjectRef gameObject);

	// GameObject 검색
	GameObjectRef Find(ObjectId id);

	// GameObject 검색
	template<GameObjectType T>
	weak_ptr<T> FindGameObject();

	// GameObject 검색
	template<GameObjectType T>
	std::vector<weak_ptr<T>> FindAllGameObjects();

	void UpdateAll();

public:
	unordered_map<ObjectId, shared_ptr<GameObject>> _gameObjects;
	vector<ObjectId> _destroyGameObjectsIds;
};

template<GameObjectType T, typename ...Args>
inline std::weak_ptr<T> GameObjectManager::Instantiate(Args && ...args)
{
	auto gameObject = make_shared<T>(std::forward<Args>(args)...);

	_gameObjects[gameObject->GetID()] = gameObject;

	return gameObject;
}

template<GameObjectType T, typename ...Args>
inline std::weak_ptr<T> GameObjectManager::Instantiate(Vector2 pos, Args && ...args)
{
	auto gameObject = make_shared<T>(std::forward<Args>(args)...);
	_gameObjects[gameObject->GetID()] = gameObject;

	gameObject->Transform()->Position() = pos;

	return gameObject;
}

template<GameObjectType T>
inline weak_ptr<T> GameObjectManager::FindGameObject()
{
	for (auto& [id, gameObject] : _gameObjects)
	{
		shared_ptr<T> casted;
		if (casted = dynamic_pointer_cast<T>(gameObject))
		{
			return casted;
		}
	}
	
	return weak_ptr<T>();
}

template<GameObjectType T>
inline std::vector<weak_ptr<T>> GameObjectManager::FindAllGameObjects()
{
	std::vector<weak_ptr<T>> result;
	for (auto& [id, gameObject] : _gameObjects)
	{
		shared_ptr<T> casted;
		if (casted = dynamic_pointer_cast<T>(gameObject))
		{
			result.push_back(casted);
		}
	}

	return result;
}

inline auto& GGameObjectManager()
{
	return GameObjectManager::Instance();
}