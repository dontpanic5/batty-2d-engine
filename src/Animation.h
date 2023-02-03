#ifndef ANIMATION_H_INCLUDED
#define ANIMATION_H_INCLUDED

#include <vector>
#include "raylib.h"

class Animation
{
public:
	Animation(unsigned int frames, const char *dir, const char *format);

	std::vector<Texture2D>& getTextures();

	const char *getDir();

protected:
	std::vector<Texture2D>	m_textures;
	const char				*m_dir;
};

#endif