#include "Actor.h"

Actor::Actor(int posX, int posY) : m_posX(posX), m_posY(posY)
{
}

Actor::Actor(int posX, int posY, float rot) :
	m_posX(posX), m_posY(posY), m_rot(rot)
{
}
