#pragma once

#include <stack>
#include "Grid.h"

class AStarManager : public Singleton<AStarManager>
{
public:
	AStarManager() : _pool(ThreadPool(2)) {}
	~AStarManager() = default;

	void FindPath(const Grid& grid, const IntPoint& start, const IntPoint& goal, int entitySize, std::function<void(std::queue<IntPoint>)> callBack)
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

private:
	ThreadPool _pool;
};

