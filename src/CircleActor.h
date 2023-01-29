#ifndef CIRCLE_ACTOR_H_INCLUDED

#include "Actor.h"

class CircleActor : public Actor
{
public:
	CircleActor(int posX, int posY);
	CircleActor(int posX, int posY, float radius, Color color);

	void UpdateActor(const GameState& gameState) override;
	void DrawActor() override;

protected:
	float	m_radius	= 10.0f;
	Color	m_color		= RED;
};

#endif // !CIRCLE_ACTOR_H_INCLUDED