#include "pch.h"
#include "NavgationAgentCompnent.h"
#include "World.h"

NavgationAgentCompnent::NavgationAgentCompnent(weak_ptr<GameObject> owner) : Component(owner)
{
	_agentIndex = World::Instance()->GetNavMesh().AddAgent(World::Instance()->GetSpawnPos(), &_agentParams);
	Log << World::Instance()->GetNavMesh().GetAgentPosition(_agentIndex) << endl;

}

NavgationAgentCompnent::~NavgationAgentCompnent()
{
	auto& navMesh = World::Instance()->GetNavMesh();
	navMesh.RemoveAgent(_agentIndex);
}

void NavgationAgentCompnent::Update(float deltaTime)
{
	auto& navMesh = World::Instance()->GetNavMesh();
	auto pos = navMesh.GetAgentPosition(_agentIndex);

	//Log << "Pos : " << pos << endl;
	Transform()->Position() = pos;

	if (Vector3::Distance(pos, _targetPos) <= 150.0f)
	{
		navMesh.StopMove(_agentIndex);
		
		return;
	}

}

void NavgationAgentCompnent::MoveTo(const Vector3& goal)
{
	auto& navMesh = World::Instance()->GetNavMesh();
	bool result = navMesh.RequestMove(_agentIndex, goal);
	if (!result)
	{
		Log << "Request Move to Invalid Position" << endl;
	}

	_targetPos = goal;
}

