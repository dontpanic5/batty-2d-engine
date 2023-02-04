#include "PlayerActor.h"
#include "AnimationMgr.h"
#include <stdio.h>
#include "GameDefs.h"
#include "GameState.h"

bool PlayerActor::m_initialized;

PlayerActor::PlayerActor(int posX, int posY)
	: Actor(posX, posY)
{
}

void PlayerActor::initPlayerActor()
{
	if (m_initialized == false)
	{
		//AnimationMgr::Instance().Add(121, "resources/swing_sword", "frame_%0.3u_delay-0.03s_out.png");
		m_initialized = true;
	}
}

bool PlayerActor::playerMoved() const
{
	return m_moved;
}

bool PlayerActor::didAttack() const
{
	return m_attacked;
}

void PlayerActor::UpdateActor(const GameState& gameState)
{
	reset();

	bool gotPress = false;

	pos myPos = { m_posX, m_posY };
	DIRECTION dir;

	if (IsKeyPressed(KEY_UP))
	{
		dir = UP;
		gotPress = true;
	}
	else if (IsKeyPressed(KEY_DOWN))
	{
		dir = DOWN;
		gotPress = true;
	}
	else if (IsKeyPressed(KEY_RIGHT))
	{
		dir = RIGHT;
		gotPress = true;
	}
	else if (IsKeyPressed(KEY_LEFT))
	{
		dir = LEFT;
		gotPress = true;
	}

	if (gotPress)
	{
		GameType obstacleHit = GT_NONE;
		m_moved = gameState.moveIfAvailable(myPos, dir, GameType::GT_PLAYER, &obstacleHit);
		if (m_moved)
		{
			m_posX = myPos.x;
			m_posY = myPos.y;
		}
		else if (obstacleHit == GT_MONSTER)
		{
			m_attacked = true;
			// we didn't move to a new square but by shooting the pump we're making a "move"
			m_moved = true;
		}
	}
}

void PlayerActor::DrawActor()
{
	DrawRectangle(unitToDirtSpaceX(m_posX), unitToDirtSpaceY(m_posY), UNIT_SIZE_PX, UNIT_SIZE_PX, BLUE);
}

void PlayerActor::reset()
{
	m_moved		= false;
	m_attacked	= false;
}
