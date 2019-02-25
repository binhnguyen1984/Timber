/*
 * FlippingObject.cpp
 *
 *  Created on: Feb 23, 2019
 *      Author: binh
 */

#include "FlippingObject.h"

FlippingObject::FlippingObject(const char *tex_path, int posX, int posY):MovingObject(tex_path, posX, posY) {
	side = Side::LEFT;
};
void FlippingObject::set_side(Side s){side = s;};
Side FlippingObject::get_side(){return side;}

FlippingObject::~FlippingObject() {
}

