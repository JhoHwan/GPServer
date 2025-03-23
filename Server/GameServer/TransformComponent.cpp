#include "pch.h"
#include "TransformComponent.h"

TransformComponent::TransformComponent(weak_ptr<GameObject> owner) : IComponent(owner), _position({0, 0}), _rotation(0), _scale({1, 1})
{
}
