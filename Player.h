/*
 * Player.h
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#define PLAYER_X 580
#define PLAYER_Y 720

#include "FlippingObject.h"

class Player: public FlippingObject{
public:
	Player();
	void flip_side();
	virtual ~Player();
};

#endif /* PLAYER_H_ */
