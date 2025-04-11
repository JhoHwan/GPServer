#include "pch.h"
#include "TransformComponent.h"

TransformComponent::TransformComponent(weak_ptr<GameObject> owner) : Component(owner), _position(Vector3::Zero()), _rotation(0), _scale(Vector3::One())
{
}
