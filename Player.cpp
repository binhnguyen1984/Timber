/*
 * Player.cpp
 *
 *  Created on: Feb 14, 2019
 *      Author: binh
 */

#include "Player.h"

Player::Player(): FlippingObject("Data/graphics/player.png", PLAYER_X, PLAYER_Y){
}
void Player::flip_side()
{
	if(side==LEFT) side = RIGHT;
	else side =LEFT;
}
Player::~Player() {
}

