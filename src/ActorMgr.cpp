#include "ActorMgr.h"

ActorMgr& ActorMgr::Instance()
{
    static ActorMgr instance;
    return instance;
}
