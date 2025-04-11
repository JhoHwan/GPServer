#include "pch.h"
#include "AStarManager.h"

#include "World.h"

void Pathfinder::FindPathAsync(const Grid& grid, const IntPoint& start, const IntPoint& goal, int entitySize, std::function<void(std::queue<IntPoint>)> callBack)
{
	_pool.Enqueue([&grid, start, goal, entitySize, callBack]()
		{
			std::queue<std::pair<int, int>> path;
			bool result = grid.FindPath(start.first, start.second, goal.first, goal.second, entitySize, path);
			if (!result)
			{
				Log << "Path not found" << endl;
				return;
			}

			callBack(path);
		});
}

void Pathfinder::FindPathAsync(const NavMeshField& navMesh, const Vector3& startPos, const Vector3& goalPos, std::function<void(std::queue<Vector3>)> callBack)
{
	_pool.Enqueue([&navMesh, startPos, goalPos, callBack]()
		{
			std::queue<Vector3> path;
			bool result = navMesh.FindPath(startPos, goalPos, path);

			callBack(path);
		});
}
