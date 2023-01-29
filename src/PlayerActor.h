#ifndef PLAYER_ACTOR_H_INCLUDED
#define PLAYER_ACTOR_H_INCLUDED

#include "Actor.h"

class PlayerActor : public Actor
{
public:
	PlayerActor(int posX, int posY);

	void UpdateActor(const GameState& gameState) override;
	void DrawActor() override;

	int getPosY() const;
	int getPosX() const;
};

#endif // !PLAYER_ACTOR_H_INCLUDED
