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
class MovingObject {
private:
	Sprite m_sprite;
	bool isActive;
	float speedX, speedY;
public:
	MovingObject(const char *tex_path, int posX, int posY);
	void set_position(int newX, int newY);
	void set_origin(int orgX, int orgY);
	void set_rotation(float angle);
	Sprite& get_sprite();
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
