#include "pch.h"

#include "Grid.h"
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;

Grid::Grid(const std::vector<std::vector<int>>& grid) : _map(grid)
{
	_height = grid.size();
	_width = grid.empty() ? 0 : grid[0].size();

	BuildClearance();
}

Grid::~Grid()
{
}

bool Grid::FindPath(int startX, int startY, int goalX, int goalY, int entitySize, OUT std::queue<IntPoint>& outPath) const
{
	if (!IsValidPosition(startX, startY, entitySize) || !IsValidPosition(goalX, goalY, entitySize)) return false;

	vector<vector<Node>> nodes(_height, vector<Node>(_width, Node(0, 0)));
	for (int i = 0; i < _height; i++)
	{
		for (int j = 0; j < _width; j++)
		{
			nodes[i][j].x = j;
			nodes[i][j].y = i;
		}
	}

	nodes[startY][startX].g = 0;
	nodes[startY][startX].h = Heuristic(startX, startY, goalX, goalY);
	nodes[startY][startX].f = nodes[startY][startX].g + nodes[startY][startX].h;

	auto cmp = [](Node* a, Node* b) { return a->f > b->f; };
	priority_queue<Node*, vector<Node*>, decltype(cmp)> openList(cmp);
	openList.push(&nodes[startY][startX]);

	vector<vector<bool>> closedList(_height, vector<bool>(_width, false));

	vector<pair<int, int>> dirs = { {0, -1}, {0, 1}, {-1, 0}, {1, 0}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1} };

	Node* goalNode = nullptr;
	while (!openList.empty())
	{
		Node* current = openList.top();
		openList.pop();

		int cx = current->x;
		int cy = current->y;

		if (cx == goalX && cy == goalY)
		{
			goalNode = current;
			break;
		}
		closedList[cy][cx] = true;

		for (auto& dir : dirs)
		{
			int nx = cx + dir.first;
			int ny = cy + dir.second;

			if (nx < 0 || ny < 0 || nx >= _width || ny >= _height) continue;

			// 대각 이동일 경우 인접한 수평, 수직 셀도 체크
			if (abs(dir.first) == 1 && abs(dir.second) == 1) {
				// (cx + dir.first, cy)와 (cx, cy + dir.second)가 모두 통과 가능한지 확인
				if (!IsValidPosition(cx + dir.first, cy, entitySize) ||
					!IsValidPosition(cx, cy + dir.second, entitySize))
				{
					continue;  // 인접 셀 중 하나라도 막혀 있으면 대각 이동 무시
				}
			}

			if (!IsValidPosition(nx, ny, entitySize)) continue;
			if (closedList[ny][nx]) continue;

			double moveCost = abs(dir.first) + abs(dir.second) == 2 ? sqrt(2) : 1.0;
			double tentativeG = current->g + moveCost;
			Node* neighbor = &nodes[ny][nx];

			if (tentativeG < neighbor->g)
			{
				neighbor->parent = current;
				neighbor->g = tentativeG;
				neighbor->h = Heuristic(nx, ny, goalX, goalY);
				neighbor->f = neighbor->g + neighbor->h;
				openList.push(neighbor);
			}
		}
	}

	stack<IntPoint> path;
	if (goalNode)
	{
		Node* current = goalNode;
		while (current)
		{
			path.emplace(current->x, current->y);
			current = current->parent;
		}
	}
	if (path.empty()) return false;

	IntPoint& prev = path.top();
	path.pop();

	IntPoint lastDir = { 0, 0 }; // 초기 방향 없음

	while (!path.empty())
	{
		IntPoint& curr = path.top(); path.pop();
		IntPoint dir = { curr.first - prev.first, curr.second - prev.second };

		if (dir.first != lastDir.first || dir.second != lastDir.second)
		{
			outPath.push(prev); // 방향 바뀌는 시점 추가
			lastDir = dir;
		}

		prev = curr;
	}
	outPath.push(prev); // 마지막 위치 추가

	return true;
}


void Grid::BuildClearance()
{
	_clearanceMap.resize(_height, std::vector<int>(_width, 0));

	for (int i = _height - 1; i >= 0; i--)
	{
		for (int j = _width - 1; j >= 0; j--)
		{
			if (_map[i][j] == 1) continue;

			if (i == _height - 1 || j == _width - 1) _clearanceMap[i][j] = 1;
            else _clearanceMap[i][j] = min(min(_clearanceMap[i + 1][j], _clearanceMap[i][j + 1]), _clearanceMap[i + 1][j + 1]) + 1;
		}
	}
}

bool Grid::IsValidPosition(int x, int y, int entitySize) const
{
	if (x < 0 || y < 0 || x >= _width || y >= _height) return false;
	return _clearanceMap[y][x] >= entitySize;
}

double Grid::Heuristic(int x1, int y1, int x2, int y2)
{
	int dx = abs(x1 - x2);
	int dy = abs(y1 - y2);
	double D = 1.0;			// 직선 이동 비용
	double D2 = sqrt(2);	// 대각선 이동 비용

	// (전체 직선 이동 비용) - ((대각선 이동 시 절약되는 비용) * (대각선 이동 횟수))
	return D * (dx + dy) - ((2 * D - D2) * min(dx, dy));
}
