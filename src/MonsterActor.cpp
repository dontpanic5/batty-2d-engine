#include "MonsterActor.h"
#include "GameDefs.h"
#include "GameState.h"

MonsterActor::MonsterActor(int posX, int posY)
	: Actor(posX, posY)
{
}

void MonsterActor::UpdateActor(const GameState& gameState)
{
	if (gameState.getPlayer().didAttack())
	{
		beAttacked();
	}
	else if (m_status == STATUS::PUMPED)
	{
		m_status = STATUS::NONE;
	}
}

void MonsterActor::DrawActor()
{
	Color color;
	if (m_status == STATUS::PUMPED)
	{
		color = DARKPURPLE;
	}
	else if (m_status == STATUS::NONE)
	{
		color = RED;
	}
	else
	{
		color = BLACK;
	}
	DrawRectangle(unitToDirtSpaceX(m_posX), unitToDirtSpaceY(m_posY), UNIT_SIZE_PX, UNIT_SIZE_PX, color);
}

STATUS MonsterActor::getStatus() const
{
	return m_status;
}

void MonsterActor::beAttacked()
{
	if (m_status == STATUS::NONE)
	{
		m_status = STATUS::PUMPED;
	}
	else if (m_status == STATUS::PUMPED)
	{
		m_status = STATUS::DEAD;
	}
}

