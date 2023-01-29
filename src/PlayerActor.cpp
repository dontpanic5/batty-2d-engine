#include "PlayerActor.h"

PlayerActor::PlayerActor(int posX, int posY)
	: Actor(posX, posY)
{
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
