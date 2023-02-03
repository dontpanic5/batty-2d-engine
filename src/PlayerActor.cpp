#include "PlayerActor.h"
#include "AnimationMgr.h"
#include <stdio.h>

bool PlayerActor::m_initialized;

PlayerActor::PlayerActor(int posX, int posY)
	: Actor(posX, posY)
{
}

void PlayerActor::initPlayerActor()
{
	if (m_initialized == false)
	{
		AnimationMgr::Instance().Add(121, "resources/swing_sword", "frame_%0.3u_delay-0.03s_out.png");
		m_initialized = true;
	}
}

void PlayerActor::UpdateActor(const GameState& gameState)
{
	if (IsKeyDown(KEY_UP))
		m_posY--;
	else if (IsKeyDown(KEY_DOWN))
		m_posY++;

	if (IsKeyDown(KEY_RIGHT))
		m_posX++;
	else if (IsKeyDown(KEY_LEFT))
		m_posX--;
}

void PlayerActor::DrawActor()
{
	
}
