#include "QuadTree.h"

#include <iostream>
#include <string>
#include <stack>

using namespace QT;
using namespace std;

QuadTree::Node::Node(int x, int y, int w, int h, int walkable) : x(x), y(y), w(w), h(h), walkable(walkable)
{
	for (int i = 0; i < 4; i++) children[i] = nullptr;
}

QuadTree::Node::~Node()
{
	// 자식 노드 메모리 해제
	for (int i = 0; i < 4; i++)
	{
		if (children[i] == nullptr) continue;

		delete children[i];
		children[i] = nullptr;
	}
}

QuadTree::QuadTree(const std::vector<std::vector<int>>& grid)
{
	int height = grid.size();
	int width = grid.empty() ? 0 : grid[0].size();

	// 루트 노드 생성
	_root = Build(grid, 0, 0, width, height);
}

QuadTree::~QuadTree()
{
	// 루트 노드 메모리 해제
	delete _root;
}

bool QuadTree::IsUniform(const std::vector<std::vector<int>>& grid, int x, int y, int width, int height, int& value) const
{
	// 첫 번째 값으로 초기화
	value = grid[y][x];

	// 주어진 영역이 균일한지 확인
	for (int i = y; i < y + height; i++)
	{
		for (int j = x; j < x + width; j++)
		{
			if (grid[i][j] != value) return false;
		}
	}

	return true;
}

struct BuildTask 
{
	int x, y, width, height;
	QuadTree::Node* parent; // 부모 노드. 루트인 경우 nullptr.
	int childIndex;         // 부모의 children 배열에서 어느 인덱스에 할당할지 (-1은 루트)
};

QuadTree::Node* QuadTree::Build(const std::vector<std::vector<int>>& grid, int x, int y, int width, int height)
{
	QuadTree::Node* root = nullptr;
	std::stack<BuildTask> tasks;
	tasks.push(BuildTask{ x, y, width, height, nullptr, -1 });

	while (!tasks.empty())
	{
		BuildTask task = tasks.top();
		tasks.pop();

		int value;
		if (IsUniform(grid, task.x, task.y, task.width, task.height, value))
		{
			// 균일한 영역이면 리프 노드를 생성
			QuadTree::Node* leaf = new QuadTree::Node(task.x, task.y, task.width, task.height, value);
			if (task.parent)
			{
				task.parent->children[task.childIndex] = leaf;
				_leafNodes.push_back(leaf);
			}
			else
			{
				root = leaf;
			}
			
			continue;
		}

		// 균일하지 않은 영역이면 내부 노드 생성 (walkable = -1)
		QuadTree::Node* node = new QuadTree::Node(task.x, task.y, task.width, task.height, -1);
		if (task.parent)
		{
			task.parent->children[task.childIndex] = node;
		}
		else
		{
			root = node;
		}

		// 영역이 더 이상 분할할 수 있는지 확인
		int midWidth = task.width / 2;
		int midHeight = task.height / 2;
		if (midWidth == 0 || midHeight == 0) continue;  // 더 이상 분할 불가

		// 네 영역에 대해 작업을 스택에 push (순서는 상관 없으나, DFS 순서를 유지하려면 순서를 조정)

		// 좌상
		tasks.push({ task.x, task.y, midWidth, midHeight, node, 0 });

		// 우상
		tasks.push({ task.x + midWidth, task.y, task.width - midWidth, midHeight, node, 1 });

		// 좌하
		tasks.push({ task.x, task.y + midHeight, midWidth, task.height - midHeight, node, 2 });

		// 우하
		tasks.push({ task.x + midWidth, task.y + midHeight, task.width - midWidth, task.height - midHeight, node, 3 });
	}

	return root;
}

void QuadTree::Print(Node* node, int depth) const
{
	if (!node) return;
	string indent(depth * 2, ' '); // 깊이에 따른 들여쓰기

	if (node->walkable != -1)  // 리프 노드 출력
	{
		cout << indent << "Leaf: (" << node->x << ", " << node->y << ", " << node->w << ", " << node->h << ") = " << node->walkable << endl;
	}
	else  // 내부 노드 출력
	{
		cout << indent << "Node: (" << node->x << ", " << node->y << ", " << node->w << ", " << node->h << ")" << endl;
		for (int i = 0; i < 4; i++) Print(node->children[i], depth + 1); // 자식 노드 출력
	}
}

void QuadTree::Print() const
{
	// 루트 노드부터 출력 시작
	Print(_root);
}