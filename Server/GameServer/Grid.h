#pragma once

#include <vector>
#include "QuadTree.h"


namespace QT
{
	constexpr double INF = std::numeric_limits<double>::infinity();

	class Grid
	{
	public:
		Grid(const std::vector<std::vector<int>>& grid);
		~Grid();

		// Getter & Setter
	public:
		inline const QT::QuadTree& GetQuadTree() const { return *_quadTree; }

		// A* Algorithm
	public:
		struct Node
		{
			int x, y;
			double g, h, f;
			Node* parent;

			Node(int x, int y) : x(x), y(y), g(INF), h(0), f(INF), parent(nullptr) {}
		};

		std::vector<std::pair<int, int>> FindPath(int startX, int startY, int endX, int endY, int entitySize);

	private:
		void BuildClearance();
		bool IsValidPosition(int x, int y, int entitySize) const;
		static double Heuristic(int x1, int y1, int x2, int y2);

	private:
		std::vector<std::vector<int>> _map;
		std::vector<std::vector<int>> _clearanceMap;
		QT::QuadTree* _quadTree;

		int _width;
		int _height;
	};
}