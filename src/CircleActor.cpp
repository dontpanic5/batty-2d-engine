#include "CircleActor.h"

CircleActor::CircleActor(int posX, int posY)
	: Actor(posX, posY)
{
}

CircleActor::CircleActor(int posX, int posY, float radius, Color color)
	: Actor(posX, posY), m_radius(radius), m_color(color)
{
}

void CircleActor::UpdateActor(const GameState& gameState)
{
	int playerX = gameState.getPlayer().getPosX();
	int playerY = gameState.getPlayer().getPosY();

	if (playerX < m_posX)
		m_posX--;
	else
		m_posX++;

	if (playerY < m_posY)
		m_posY--;
	else
		m_posY++;
}

void CircleActor::DrawActor()
{
	DrawCircle(m_posX, m_posY, m_radius, m_color);
}
