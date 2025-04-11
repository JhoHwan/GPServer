#pragma once

#include <stack>
#include "Grid.h"

class NavMeshField;

class Pathfinder : public Singleton<Pathfinder>
{
public:
	Pathfinder() : _pool(ThreadPool(2)) {}
	~Pathfinder() = default;

	void FindPathAsync
	(const Grid& grid, const IntPoint& start, const IntPoint& goal,
		int entitySize, std::function<void(std::queue<IntPoint>)> callBack);

	void FindPathAsync(const NavMeshField& navMesh, const Vector3& startPos, const Vector3& goalPos, std::function<void(std::queue<Vector3>)> callBack);

private:
	ThreadPool _pool;
};

