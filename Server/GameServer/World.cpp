#include "pch.h"
#include "World.h"

#include "DetourCrowd.h"
#include "DetourNavMesh.h"
#include "DetourNavMeshQuery.h"

World::World() : _spawnPos(Vector3(-3872.318840, -1356.427767, 533.844949))
{
}

World::~World()
{

}

void World::Update(const float deltaTime)
{
	_navMesh.Update(deltaTime);
}

void World::FindPathAsync(const Vector3& startPos, const Vector3& goalPos, std::function<void(std::queue<Vector3>)> callBack)
{
	Pathfinder::Instance()->FindPathAsync(GetNavMesh(), startPos, goalPos, callBack);
}

NavMeshField::NavMeshField()
{
	_navMesh = NavMeshReader::DeSerializedtNavMesh("..\\Resources\\NavMesh\\Map1.bin");
	_navQuery = dtAllocNavMeshQuery();
	_navQuery->init(_navMesh, 2048);

	_crowd = dtAllocCrowd();
	_crowd->init(1024, 1, _navMesh);
}

NavMeshField::~NavMeshField()
{
	dtFreeNavMesh(_navMesh);
	dtFreeNavMeshQuery(_navQuery);
}

void NavMeshField::Update(const float deltaTime)
{
	_crowd->update(0.33f, nullptr);
}

int32 NavMeshField::AddAgent(const Vector3& startPos, const dtCrowdAgentParams* params)
{
	auto position = Unreal2RecastPoint(startPos).data();

	float nearPos[3];

	auto fillter = _crowd->getFilter(0);
	auto extents = _crowd->getQueryExtents();

	dtPolyRef ref;

	_navQuery->findNearestPoly(position, extents, fillter, &ref, nearPos);

	return _crowd->addAgent(nearPos, params);
}

Vector3 NavMeshField::GetAgentPosition(int32 agentIndex)
{
	const dtCrowdAgent* agent = _crowd->getAgent(agentIndex);

	return Recast2UnrealPoint(agent->npos);
}

float NavMeshField::GetAgentVelocity(int32 agentIndex)
{
	auto* agent = _crowd->getAgent(agentIndex);
	return Recast2UnrealPoint(agent->npos).Length();
}

void NavMeshField::RemoveAgent(int32 index)
{
	_crowd->removeAgent(index);
}

bool NavMeshField::RequestMove(int32 agentIndex, const Vector3& goal)
{
	const float* goalPos = Unreal2RecastPoint(goal).data();

	auto fillter = _crowd->getFilter(0);
	auto extents = _crowd->getQueryExtents();

	dtPolyRef ref;
	float nearestPoint[3];

	dtStatus status = _navQuery->findNearestPoly(goalPos, extents, fillter, &ref, nearestPoint);
	if (!dtStatusSucceed(status)) return false;

	return _crowd->requestMoveTarget(agentIndex, ref, nearestPoint);
}

void NavMeshField::StopMove(int32 agentIndex)
{ 
	_crowd->resetMoveTarget(agentIndex);
}

bool NavMeshField::FindPath(const Vector3& start, const Vector3& goal, OUT std::queue<Vector3>& outPath) const
{
	dtPolyRef startPoly;
	float startPoint[3];

	bool result = FindNearestPoly(start, startPoly, startPoint);
	if (!result)
	{
		Log << "Fail FindNearestPoly" << endl;
		return false;
	}

	dtPolyRef goalPoly;
	float goalPoint[3];

	result = FindNearestPoly(goal, goalPoly, goalPoint);
	if (!result)
	{
		Log << "Fail FindNearestPoly" << endl;
		return false;
	}

	auto fillter = _crowd->getFilter(0);
	auto extents = _crowd->getQueryExtents();
	const int32 MAXPATH = 256;

	dtPolyRef paths[MAXPATH];
	int pathCount;
	if(dtStatusFailed(_navQuery->findPath(startPoly, goalPoly, startPoint, goalPoint, fillter, paths, &pathCount, MAXPATH)))
	{
		Log << "Fail findPath" << endl;
		return false;
	}
	
	float pathPoints[MAXPATH][3];
	unsigned char flags[MAXPATH];
	int straightCount = 0;
	dtPolyRef straightRefs[MAXPATH];

	if (dtStatusFailed(_navQuery->findStraightPath(startPoint, goalPoint, paths, pathCount, &pathPoints[0][0], flags, straightRefs, &straightCount, MAXPATH)))
	{
		Log << "Fail findPath" << endl;
		return false;
	}

	for (int32 i = 0; i < straightCount; i++)
	{
		outPath.emplace(Recast2UnrealPoint(pathPoints[i]));
		Log << Recast2UnrealPoint(pathPoints[i]) << endl;
	}

	return true;
}

bool NavMeshField::GetHeightOnNavMesh(Vector3& vector)
{
	float* pos = Unreal2RecastPoint(vector).data();

	float nearestPoint[3];
	dtPolyRef polyRef;

	// 1. 주어진 x, z 좌표 근처에서 가장 가까운 폴리곤을 찾는다
	dtStatus status = _navQuery->findNearestPoly(pos, _crowd->getQueryExtents(), _crowd->getFilter(0), &polyRef, nearestPoint);
	if (dtStatusFailed(status) || polyRef == 0)
		return false;

	// 2. 해당 poly 위의 정확한 높이를 구한다
	float height;
	status = _navQuery->getPolyHeight(polyRef, nearestPoint, &height);
	if (dtStatusFailed(status))
		return false;

	pos[1] = height;

	vector = Recast2UnrealPoint(pos);
	return true;
}

bool NavMeshField::FindNearestPoly(const Vector3& pos, OUT dtPolyRef& outRef, OUT float* outPoint) const
{
	auto* extend = _crowd->getQueryExtents();
	auto* fillter = _crowd->getFilter(0);

	const float* center = Unreal2RecastPoint(pos).data();

	auto result = _navQuery->findNearestPoly(center, extend, fillter, &outRef, outPoint);

	return dtStatusSucceed(result);
}
