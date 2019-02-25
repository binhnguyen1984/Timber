/*
 * FlippingObject.h
 *
 *  Created on: Feb 23, 2019
 *      Author: binh
 */

#ifndef FLIPPINGOBJECT_H_
#define FLIPPINGOBJECT_H_

#include "MovingObject.h"
typedef enum {NONE, LEFT, RIGHT} Side;

class FlippingObject: public MovingObject {
protected:
	Side side;
public:
	FlippingObject(const char *tex_path, int posX,  int posY);
	virtual ~FlippingObject();
	void set_side(Side s);
	Side get_side();
};
#endif /* FLIPPINGOBJECT_H_ */
