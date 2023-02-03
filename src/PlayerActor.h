#ifndef PLAYER_ACTOR_H_INCLUDED
#define PLAYER_ACTOR_H_INCLUDED

#include "Actor.h"

constexpr unsigned int FRAME_COUNT = 122;

class GameState;

class PlayerActor : public Actor
{
public:
	PlayerActor(int posX, int posY);

	void initPlayerActor();

	void UpdateActor(const GameState& gameState) override;
	void DrawActor() override;

protected:
	static bool			m_initialized;
};

#endif // !PLAYER_ACTOR_H_INCLUDED
