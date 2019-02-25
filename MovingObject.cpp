/*
 * MovingObject.cpp
 */

#include "MovingObject.h"
#include "TextureLoader.h"
MovingObject::MovingObject(const char *tex_path, int posX, int posY):Sprite(TextureLoader::getTexture(tex_path)){
	setPosition(posX, posY);
	speedX = speedY=0;
	isActive = false;
}

void MovingObject::set_active_state(bool s) {isActive = s;}
bool& MovingObject::get_state() {return isActive;}
void MovingObject::set_speed_X(float speedX) { this->speedX = speedX;}
void MovingObject::set_speed_Y(float speedY) { this->speedY = speedY;}
float& MovingObject::get_speed_X(){return speedX;}
float& MovingObject::get_speed_Y(){return speedY;}
int MovingObject::getX(){return getPosition().x;}
int MovingObject::getY(){return getPosition().y;}
MovingObject::~MovingObject() {
}

