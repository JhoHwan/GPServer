#pragma once
#include <stack>
#include "Grid.h"

class World : public Singleton<World>
{
	enum { CELL_SIZE = 80 };

public:
	World() : _grid(nullptr) {}
	~World() {}

public:
	void Init(const std::vector<std::vector<int>>& grid)
	{
		_grid = std::make_unique<Grid>(grid);
	}

	void FindPathAsync(const Vector2& start, const Vector2& goal, int entitySize, std::function<void(std::queue<IntPoint>)> callBack) const
	{
		if (!IsValidPos(start) || !IsValidPos(goal)) return;
		AStarManager::Instance()->FindPath(*_grid, WorldPosToGridPos(start), WorldPosToGridPos(goal), entitySize, callBack);
	}

	bool IsValidPos(const Vector2& pos) const
	{
		IntPoint gridPos = WorldPosToGridPos(pos);
		return _grid->IsValidPosition(gridPos.first, gridPos.second, 1);
	}

	inline static Vector2 GridPosToWorldPos(const IntPoint& gridPos)
	{
		double x = gridPos.second * CELL_SIZE;
		return Vector2(-x, gridPos.first * CELL_SIZE);
	}

	inline static IntPoint WorldPosToGridPos(const Vector2& worldPos)
	{
		return IntPoint(worldPos.y / CELL_SIZE, -1 * (worldPos.x / CELL_SIZE));
	}

private:
	std::unique_ptr<Grid> _grid;
};
