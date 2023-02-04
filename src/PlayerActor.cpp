#include "PlayerActor.h"
#include "AnimationMgr.h"
#include <stdio.h>
#include "GameDefs.h"
#include "GameState.h"

bool		PlayerActor::m_initialized;
Texture2D	PlayerActor::s_miner;
Texture2D	PlayerActor::s_pumpL;
Texture2D	PlayerActor::s_pumpR;
Texture2D	PlayerActor::s_ded;

PlayerActor::PlayerActor(int posX, int posY)
	: Actor(posX, posY)
{
}

void PlayerActor::initPlayerActor()
{
	if (m_initialized == false)
	{
		//AnimationMgr::Instance().Add(121, "resources/swing_sword", "frame_%0.3u_delay-0.03s_out.png");

		s_miner		= LoadTexture("resources/miner.png");
		s_pumpR		= LoadTexture("resources/miner_pump.png");
		s_ded		= LoadTexture("resources/miner_ded.png");

		Image pumpL	= LoadImage("resources/miner_pump.png");
		ImageFlipHorizontal(&pumpL);
		s_pumpL		= LoadTextureFromImage(pumpL);

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
			m_dir = dir;
		}
		else if (obstacleHit == GT_MONSTER)
		{
			m_attacked = true;
			m_status = PPTD_ATTACKING;
			// we didn't move to a new square but by shooting the pump we're making a "move"
			m_moved = true;
		}
		if (obstacleHit != GT_MONSTER)
		{
			m_status = PPTD_STANDING;
		}
	}
}

void PlayerActor::UpdateDeath(const GameState& gameState)
{
	pos closestRoot = gameState.closestRootToPlayer();
	if (closestRoot.x == m_posX && closestRoot.y == m_posY)
		m_status = PPTD_DEAD;
}

void PlayerActor::DrawActor()
{
	Texture2D tex;
	if (m_status == PPTD_ATTACKING)
	{
		if (m_dir == LEFT)
			tex = s_pumpL;
		else
			tex = s_pumpR;
	}
	else if (m_status == PPTD_DEAD)
	{
		tex = s_ded;
	}
	else
	{
		tex = s_miner;
	}

	float scale = (float)UNIT_SIZE_PX / (float)tex.height;
	DrawTextureEx(tex, { (float)unitToDirtSpaceX(m_posX), (float)unitToDirtSpaceY(m_posY) }, 0.0f, scale, WHITE);
}

PLAYER_STATUS PlayerActor::getStatus() const
{
	return m_status;
}

void PlayerActor::reset()
{
	m_moved		= false;
	m_attacked	= false;
}
