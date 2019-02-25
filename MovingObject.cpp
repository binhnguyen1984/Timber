/*
 * MovingObject.cpp
 */

#include "MovingObject.h"
#include "TextureLoader.h"
MovingObject::MovingObject(const char *tex_path, int posX, int posY) {
	m_sprite = Sprite(TextureLoader::getTexture(tex_path));
	set_position(posX, posY);
	speedX = speedY=0;
	isActive = false;
}

void MovingObject::set_position(int newX, int newY)
{
	m_sprite.setPosition(newX, newY);
}

void MovingObject::set_origin(int orgX, int orgY)
{
	m_sprite.setOrigin(orgX, orgY);
}

void MovingObject::set_rotation(float angle)
{
	m_sprite.setRotation(angle);
}
Sprite& MovingObject::get_sprite()
{
	return m_sprite;
}

void MovingObject::set_active_state(bool s) {isActive = s;}
bool& MovingObject::get_state() {return isActive;}
void MovingObject::set_speed_X(float speedX) { this->speedX = speedX;}
void MovingObject::set_speed_Y(float speedY) { this->speedY = speedY;}
float& MovingObject::get_speed_X(){return speedX;}
float& MovingObject::get_speed_Y(){return speedY;}
int MovingObject::getX(){return m_sprite.getPosition().x;}
int MovingObject::getY(){return m_sprite.getPosition().y;}
MovingObject::~MovingObject() {
}

