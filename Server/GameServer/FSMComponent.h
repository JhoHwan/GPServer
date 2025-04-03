#pragma once
#include "Component.h"
class FSMComponent : public Component
{
public:
	FSMComponent(std::weak_ptr<GameObject> owner);

	virtual ~FSMComponent() {}

	virtual void Update(float deltaTime) override = 0;
};	

