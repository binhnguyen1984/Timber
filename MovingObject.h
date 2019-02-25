/*
 * MovingObject.h
 *
 *  Created on: Feb 12, 2019
 *      Author: binh
 */

#ifndef MOVINGOBJECT_H_
#define MOVINGOBJECT_H_
#include <SFML/Graphics.hpp>
using namespace sf;
class MovingObject: public Sprite{
private:
	bool isActive;
	float speedX, speedY;
public:
	MovingObject(const char *tex_path, int posX, int posY);
	virtual ~MovingObject();
	void set_active_state(bool s);
	bool& get_state();
	void set_speed_X(float speedX);
	void set_speed_Y(float speedY);
	float& get_speed_X();
	float& get_speed_Y();
	int getX();
	int getY();
};

#endif /* MOVINGOBJECT_H_ */
