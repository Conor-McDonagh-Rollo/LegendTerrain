#ifndef OBJECT_H
#define OBJECT_H

class Object {
public:
	Object() {}
	virtual void draw() = 0;
	virtual void move(float x = 0.f, float y = 0.f, float z = 0.f) = 0;
	virtual void rotate(float x = 0.f, float y = 0.f, float z = 0.f) = 0;
};

#endif