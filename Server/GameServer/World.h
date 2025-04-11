#pragma once
#include <stack>
#include "Grid.h"

#include "NavMeshReader.h"
#include "DetourNavMeshQuery.h"
#include "DetourCrowd.h"

class NavMeshField
{
public:
	NavMeshField();

	~NavMeshField();

	void Update(const float deltaTime);

	int32 AddAgent(const Vector3& startPos, const dtCrowdAgentParams* params);

	Vector3 GetAgentPosition(int32 agentIndex);

	float GetAgentVelocity(int32 agentIndex);

	void RemoveAgent(int32 index);

	bool RequestMove(int32 agentIndex, const Vector3& goal);
	void StopMove(int32 agentIndex);

	bool FindPath(const Vector3& start, const Vector3& goal, OUT std::queue<Vector3>& outPath) const;

	bool GetHeightOnNavMesh(Vector3& vector);

private:
	inline static Vector3 Recast2UnrealPoint(const float* pos)
	{
		return Vector3(-pos[0] * 100, -pos[2] * 100, pos[1] * 100);
	}

	inline static std::array<float, 3> Unreal2RecastPoint(const Vector3& vector)
	{
		return std::array<float, 3>{(float)(-vector.x / 100), (float)(vector.z / 100), (float)(-vector.y / 100)};
	}


	bool FindNearestPoly(const Vector3& pos, OUT dtPolyRef& outRef, OUT float* outPoint) const;

private:
	dtNavMesh* _navMesh;
	dtNavMeshQuery* _navQuery;
	dtCrowd* _crowd;
};

class World : public Singleton<World>
{
	enum { CELL_SIZE = 80 };

public:
	World();
	~World();

public:
	void Update(const float deltaTime);

	void FindPathAsync(const Vector3& startPos, const Vector3& goalPos, std::function<void(std::queue<Vector3>)> callBack);

public:
	inline Vector3 GetSpawnPos() const { return _spawnPos; }
	inline NavMeshField& GetNavMesh() { return _navMesh; }

private:
	Vector3 _spawnPos;

	NavMeshField _navMesh;

	std::unique_ptr<Grid> _grid;


};
