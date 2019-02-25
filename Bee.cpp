/*
 * Bee.cpp
 *
 *  Created on: Feb 15, 2019
 *      Author: binh
 */

#include "Bee.h"

Bee::Bee(): MovingObject("Data/graphics/bee.png", 0, 800) {
	isActive = false;
	speed=0;
}

Bee::~Bee() {
}

