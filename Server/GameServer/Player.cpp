#include "pch.h"
#include "Player.h"

Player::~Player()
{
}

void Player::SetPlayerInfo(OUT Protocol::PlayerInfo* const info)
{
	info->set_x(Transform()->Position().x);
	info->set_y(Transform()->Position().y);
	info->set_object_id(GetID());
}
