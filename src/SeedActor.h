#ifndef SEED_ACTOR_H_INCLUDED
#define SEED_ACTOR_H_INCLUDED

#include "Actor.h"

class SeedActor : public Actor
{
public:
	SeedActor();

	SeedActor(int posX, int posY);

	void initSeedActor();

	void UpdateActor(const GameState& gameState) override;
	void DrawActor(const GameState& gameState) override;

protected:
	static bool m_initialized;
	static Texture2D seed;
};
#endif // !SEED_ACTOR_H_INCLUDED
