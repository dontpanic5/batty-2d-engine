#ifndef ACTORMGR_H_INCLUDED
#define ACTORMGR_H_INCLUDED

#include <unordered_map>

#include "Actor.h"

class ActorMgr
{
public:
	ActorMgr() = default;

	static ActorMgr& Instance();

	std::unordered_map<char*, Actor*> m_actors;

private:
	ActorMgr();
	ActorMgr(ActorMgr const&) = delete;
	ActorMgr& operator=(ActorMgr const&) = delete;
};

#endif