#include "MonsterActor.h"
#include "GameDefs.h"
#include "GameState.h"

bool MonsterActor::m_initialized = false;

Texture2D MonsterActor::alive;
Texture2D MonsterActor::pumped;
Texture2D MonsterActor::dead;

MonsterActor::MonsterActor(int posX, int posY)
	: Actor(posX, posY)
{
}

void MonsterActor::initMonsterActor()
{
	if (m_initialized == false)
	{
		alive	= LoadTexture("resources/monster.png");
		pumped	= LoadTexture("resources/inflated_monster.png");
		dead	= LoadTexture("resources/dead_monster.png");
		m_initialized = true;
	}
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

void MonsterActor::DrawActor(const GameState& gameState)
{
	Texture2D tex;
	if (m_status == STATUS::PUMPED)
	{
		tex = pumped;
	}
	else if (m_status == STATUS::NONE)
	{
		tex = alive;
	}
	else
	{
		tex = dead;
	}


	float scale = (float)gameState.getUnitSzPx() / (float)tex.height;
	DrawTextureEx(
		tex,
		{ (float)gameState.unitToDirtSpaceX(m_posX), (float)gameState.unitToDirtSpaceY(m_posY) },
		0.0f, scale, WHITE);
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

