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
	// �ڽ� ��� �޸� ����
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

	// ��Ʈ ��� ����
	_root = Build(grid, 0, 0, width, height);
}

QuadTree::~QuadTree()
{
	// ��Ʈ ��� �޸� ����
	delete _root;
}

bool QuadTree::IsUniform(const std::vector<std::vector<int>>& grid, int x, int y, int width, int height, int& value) const
{
	// ù ��° ������ �ʱ�ȭ
	value = grid[y][x];

	// �־��� ������ �������� Ȯ��
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
	QuadTree::Node* parent; // �θ� ���. ��Ʈ�� ��� nullptr.
	int childIndex;         // �θ��� children �迭���� ��� �ε����� �Ҵ����� (-1�� ��Ʈ)
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
			// ������ �����̸� ���� ��带 ����
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

		// �������� ���� �����̸� ���� ��� ���� (walkable = -1)
		QuadTree::Node* node = new QuadTree::Node(task.x, task.y, task.width, task.height, -1);
		if (task.parent)
		{
			task.parent->children[task.childIndex] = node;
		}
		else
		{
			root = node;
		}

		// ������ �� �̻� ������ �� �ִ��� Ȯ��
		int midWidth = task.width / 2;
		int midHeight = task.height / 2;
		if (midWidth == 0 || midHeight == 0) continue;  // �� �̻� ���� �Ұ�

		// �� ������ ���� �۾��� ���ÿ� push (������ ��� ������, DFS ������ �����Ϸ��� ������ ����)

		// �»�
		tasks.push({ task.x, task.y, midWidth, midHeight, node, 0 });

		// ���
		tasks.push({ task.x + midWidth, task.y, task.width - midWidth, midHeight, node, 1 });

		// ����
		tasks.push({ task.x, task.y + midHeight, midWidth, task.height - midHeight, node, 2 });

		// ����
		tasks.push({ task.x + midWidth, task.y + midHeight, task.width - midWidth, task.height - midHeight, node, 3 });
	}

	return root;
}

void QuadTree::Print(Node* node, int depth) const
{
	if (!node) return;
	string indent(depth * 2, ' '); // ���̿� ���� �鿩����

	if (node->walkable != -1)  // ���� ��� ���
	{
		cout << indent << "Leaf: (" << node->x << ", " << node->y << ", " << node->w << ", " << node->h << ") = " << node->walkable << endl;
	}
	else  // ���� ��� ���
	{
		cout << indent << "Node: (" << node->x << ", " << node->y << ", " << node->w << ", " << node->h << ")" << endl;
		for (int i = 0; i < 4; i++) Print(node->children[i], depth + 1); // �ڽ� ��� ���
	}
}

void QuadTree::Print() const
{
	// ��Ʈ ������ ��� ����
	Print(_root);
}