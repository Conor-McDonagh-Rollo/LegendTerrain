#ifndef PLANE_H
#define PLANE_H

#include "Textured_Object.h"

class Plane : public Textured_Object
{
public:
	Plane(Position pos = {0,0,0}, const char* tex_path = "assets/defaults/default_texture.jpg");

};

#endif