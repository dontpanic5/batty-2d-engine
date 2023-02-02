#include "PlayerActor.h"

bool PlayerActor::m_swingswordInit = false;

PlayerActor::PlayerActor(int posX, int posY)
	: Actor(posX, posY)
{
	if (m_swingswordInit == false)
	{
		for (unsigned int i = 0; i < FRAME_COUNT; i++)
		{
			m_swingsword[i] =
				LoadTexture("resources/swing_sword/frame_%0.3u_delay-0.03s_out.png");
		}
		m_swingswordInit = true;
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
	DrawCircle(m_posX, m_posY, 10, GREEN);
}
