#pragma once

#undef max
#undef min

#include "Component.h"

#include "DetourCrowd.h"


class NavgationAgentCompnent : public Component
{
public:
    NavgationAgentCompnent(weak_ptr<GameObject> owner);
    ~NavgationAgentCompnent();

    void Update(float deltaTime) override;

    void MoveTo(const Vector3& goal);

public:
    void SetSpeed(float speed) 
    { 
        _agentParams.maxSpeed = speed; 

    }

private:
    int32 _agentIndex;

    Vector3 _targetPos;

    dtCrowdAgentParams _agentParams
    {
        .radius = 1,
        .height = 1.44,
        .maxAcceleration = std::numeric_limits<float>::max(),
        .maxSpeed = 0.8,
        .collisionQueryRange = 12.0f,
        .pathOptimizationRange = 30.0f,
        .separationWeight = 2.0f,
        .updateFlags =
            DT_CROWD_ANTICIPATE_TURNS |
            DT_CROWD_OPTIMIZE_VIS |
            DT_CROWD_OBSTACLE_AVOIDANCE,
        .obstacleAvoidanceType = (unsigned char)3,
        .queryFilterType = 0,
        .userData = nullptr
    };
};
