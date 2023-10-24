#ifndef SPRITE_H
#define SPRITE_H

#include "Textured_Object.h"

class Sprite : public Textured_Object
{
public:
	Sprite(Position pos = { 0,0,0 }, const char* tex_path = "assets/defaults/default_texture.jpg");

};



#endif