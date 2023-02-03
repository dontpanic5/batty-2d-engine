#include "Animation.h"
#include <string.h>
#include "raylib.h"

Animation::Animation(unsigned int frames, const char* dir, const char* format)
	: m_dir(dir)
{
	m_textures.reserve(frames);

	for (unsigned int i = 0; i < frames; i++)
	{
		char fileFormat[128];
		sprintf(fileFormat, format, i);

		char name[128];
		sprintf(name, "%s/%s", m_dir, fileFormat);

		m_textures.push_back(LoadTexture(name));
	}
}

std::vector<Texture2D>& Animation::getTextures()
{
	return m_textures;
}

const char* Animation::getDir()
{
	return m_dir;
}
