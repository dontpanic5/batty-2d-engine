#ifndef ANIMATION_MGR_H_INCLUDED
#define ANIMATION_MGR_H_INCLUDED

#include <unordered_map>
#include "Animation.h"

class AnimationMgr final
{
public:
	static AnimationMgr& Instance();

	void Add(unsigned int frames, const char *dir, const char *format);

	void Unload();

protected:
	std::unordered_map<const char*, Animation> m_animations;
};

#endif // !ANIMATION_MGR_H_INCLUDED
