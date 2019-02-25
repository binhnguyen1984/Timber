/*
 * Bee.h
 *
 *  Created on: Feb 15, 2019
 *      Author: binh
 */

#ifndef BEE_H_
#define BEE_H_
#include "MovingObject.h"
class Bee : public MovingObject {
private:
	bool isActive;
	int speed;
public:
	Bee();
	virtual ~Bee();
};

#endif /* BEE_H_ */
