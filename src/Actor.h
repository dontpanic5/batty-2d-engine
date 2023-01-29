#ifndef ACTOR_H_INCLUDED

#include "raylib.h"
#include "raymath.h"
#include "GameState.h"

class GameState;

class Actor
{
public:
	Actor(int posX, int posY);
	Actor(int posX, int posY, float rot);

	virtual void UpdateActor(const GameState& gameState) = 0;
	virtual void DrawActor() = 0;

protected:
	int		m_posX;
	int		m_posY;
	float	m_rot		= 0.0f;
	Vector2	m_velocity	= {0.0f, 0.0f};
};
#endif // !ACTOR_H_INCLUDED