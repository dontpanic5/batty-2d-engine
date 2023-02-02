#include "Actor.h"

Actor::Actor(int posX, int posY) : m_posX(posX), m_posY(posY)
{
}

Actor::Actor(int posX, int posY, float rot) :
	m_posX(posX), m_posY(posY), m_rot(rot)
{
}

int Actor::getPosX() const
{
	return m_posX;
}

int Actor::getPosY() const
{
	return m_posY;
}
