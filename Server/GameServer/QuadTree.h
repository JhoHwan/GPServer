#include <vector>

namespace QT
{
	class QuadTree
	{
	public:
		class Node;

	public:
		// 생성자: 주어진 그리드를 사용하여 QuadTree 객체를 초기화
		QuadTree(const std::vector<std::vector<int>>& grid);

		// 복사 생성자 및 대입 연산자 삭제
		QuadTree(const QuadTree& other) = delete;
		void operator=(const QuadTree& other) = delete;
		
		// 소멸자: QuadTree 객체를 소멸시
		~QuadTree();

		// QuadTree 전체를 출력
		void Print() const;

		// Root Getter함수
		inline const Node& GetRoot() const { return *_root; }

		inline const std::vector<Node*>& GetLeafNodes() const { return _leafNodes; }

	private:
		// 주어진 영역이 균일한지 확인
		// grid: 그리드 데이터
		// x, y: 영역의 시작 좌표
		// width, height: 영역의 크기
		// value: 균일한 값 (출력 매개변수)
		// 반환값: 영역이 균일하면 true, 그렇지 않으면 false
		bool IsUniform(const std::vector<std::vector<int>>& grid, int x, int y, int width, int height, int& value) const;
		
		// 주어진 영역을 기반으로 QuadTree를 빌드
		// grid: 그리드 데이터
		// x, y: 영역의 시작 좌표
		// width, height: 영역의 크기
		// 반환값: 생성된 QuadTree 노드
		Node* Build(const std::vector<std::vector<int>>& grid, int x, int y, int width, int height);
		
		// 주어진 노드를 깊이에 따라 출력
		// node: 출력할 노드
		// depth: 현재 깊이 (기본값: 0)
		void Print(Node* node, int depth = 0) const;

	private:
		Node* _root; // QuadTree의 루트 노드
		std::vector<Node*> _leafNodes;
	};

	class QuadTree::Node
	{
	public:
		// 생성자: 주어진 좌표와 크기, walkable 값을 사용하여 노드를 초기화
		Node(int x, int y, int w, int h, int walkable = -1);
	
		// 소멸자: 노드를 소멸
		~Node();

	public:
		int x, y; // 노드의 시작 좌표
		int w, h; // 노드의 크기
		int walkable; // 노드의 walkable 값
		Node* children[4]; // 자식 노드들
	};
}
