#ifndef PLAYER_ACTOR_H_INCLUDED
#define PLAYER_ACTOR_H_INCLUDED

#include "Actor.h"

constexpr unsigned int FRAME_COUNT = 122;

class GameState;

class PlayerActor : public Actor
{
public:
	PlayerActor(int posX, int posY);

	void UpdateActor(const GameState& gameState) override;
	void DrawActor() override;

protected:
	static Texture2D	m_swingsword[FRAME_COUNT];
	static bool			m_swingswordInit;
};

#endif // !PLAYER_ACTOR_H_INCLUDED
