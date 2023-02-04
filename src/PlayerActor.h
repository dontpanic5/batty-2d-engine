#ifndef PLAYER_ACTOR_H_INCLUDED
#define PLAYER_ACTOR_H_INCLUDED

#include "Actor.h"
#include "GameDefs.h"

constexpr unsigned int FRAME_COUNT = 122;

class GameState;

enum PlayerPoseToDraw
{
	PPTD_STANDING,
	PPTD_ATTACKING
};

class PlayerActor : public Actor
{
public:
	PlayerActor(int posX, int posY);

	void initPlayerActor();

	bool playerMoved() const;
	bool didAttack() const;

	void UpdateActor(const GameState& gameState) override;
	void DrawActor() override;

protected:
	static bool			m_initialized;
	static Texture2D	s_miner;
	static Texture2D	s_pumpR;
	static Texture2D	s_pumpL;

	bool				m_moved				= false;
	bool				m_attacked			= false;
	PlayerPoseToDraw	pose				= PPTD_STANDING;
	DIRECTION			m_dir				= DIRECTION::DIR_NONE;

	void reset();
};

#endif // !PLAYER_ACTOR_H_INCLUDED
