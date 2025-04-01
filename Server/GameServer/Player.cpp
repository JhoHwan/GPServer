#include "pch.h"
#include "Player.h"
#include "PlayerControllerComponent.h"

Player::Player() : GameObject()
{
}

Player::~Player()
{
}

void Player::Init()
{
	GameObject::Init();

	AddComponent<PlayerControllerComponent>();

	GGameObjectManager()->AddPlayer(GetID());
}



