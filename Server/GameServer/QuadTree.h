#include <vector>

namespace QT
{
	class QuadTree
	{
	public:
		class Node;

	public:
		// ������: �־��� �׸��带 ����Ͽ� QuadTree ��ü�� �ʱ�ȭ
		QuadTree(const std::vector<std::vector<int>>& grid);

		// ���� ������ �� ���� ������ ����
		QuadTree(const QuadTree& other) = delete;
		void operator=(const QuadTree& other) = delete;
		
		// �Ҹ���: QuadTree ��ü�� �Ҹ��
		~QuadTree();

		// QuadTree ��ü�� ���
		void Print() const;

		// Root Getter�Լ�
		inline const Node& GetRoot() const { return *_root; }

		inline const std::vector<Node*>& GetLeafNodes() const { return _leafNodes; }

	private:
		// �־��� ������ �������� Ȯ��
		// grid: �׸��� ������
		// x, y: ������ ���� ��ǥ
		// width, height: ������ ũ��
		// value: ������ �� (��� �Ű�����)
		// ��ȯ��: ������ �����ϸ� true, �׷��� ������ false
		bool IsUniform(const std::vector<std::vector<int>>& grid, int x, int y, int width, int height, int& value) const;
		
		// �־��� ������ ������� QuadTree�� ����
		// grid: �׸��� ������
		// x, y: ������ ���� ��ǥ
		// width, height: ������ ũ��
		// ��ȯ��: ������ QuadTree ���
		Node* Build(const std::vector<std::vector<int>>& grid, int x, int y, int width, int height);
		
		// �־��� ��带 ���̿� ���� ���
		// node: ����� ���
		// depth: ���� ���� (�⺻��: 0)
		void Print(Node* node, int depth = 0) const;

	private:
		Node* _root; // QuadTree�� ��Ʈ ���
		std::vector<Node*> _leafNodes;
	};

	class QuadTree::Node
	{
	public:
		// ������: �־��� ��ǥ�� ũ��, walkable ���� ����Ͽ� ��带 �ʱ�ȭ
		Node(int x, int y, int w, int h, int walkable = -1);
	
		// �Ҹ���: ��带 �Ҹ�
		~Node();

	public:
		int x, y; // ����� ���� ��ǥ
		int w, h; // ����� ũ��
		int walkable; // ����� walkable ��
		Node* children[4]; // �ڽ� ����
	};
}
