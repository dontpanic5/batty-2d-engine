#include "AnimationMgr.h"
#include "raylib.h"
#include <vector>

AnimationMgr& AnimationMgr::Instance()
{
    static AnimationMgr instance;
    return instance;
}

void AnimationMgr::Add(unsigned int frames, const char* dir, const char* format)
{
    m_animations.emplace(std::make_pair(dir, Animation(frames, dir, format)));
}

void AnimationMgr::Unload()
{
    for (auto& anim : m_animations)
    {
        std::vector<Texture2D>& textures = anim.second.getTextures();
        for (unsigned int i = 0; i < textures.size(); i++)
        {
            UnloadTexture(textures[i]);
        }
    }
}