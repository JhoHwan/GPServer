#pragma once

#include <vector>
#include <queue>

constexpr double INF = std::numeric_limits<double>::infinity();
using IntPoint = std::pair<int32, int32>;
class Grid
{
public:
	Grid() = default;
	Grid(const std::vector<std::vector<int>>& grid);
	~Grid();

public:
	struct Node;

	bool FindPath(int startX, int startY, int goalX, int goalY, int entitySize, OUT std::queue<IntPoint>& outPath) const;
	bool IsValidPosition(int x, int y, int entitySize) const;

private:
	void BuildClearance();
	static double Heuristic(int x1, int y1, int x2, int y2);

private:
	std::vector<std::vector<int>> _map;
	std::vector<std::vector<int>> _clearanceMap;

	int _width;
	int _height;
};

struct Grid::Node
{
	int x, y;
	double g, h, f;
	Node* parent;

	Node(int x, int y) : x(x), y(y), g(INF), h(0), f(INF), parent(nullptr) {}
};