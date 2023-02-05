#ifndef MONSTER_ACTOR_H_INCLUDED
#define MONSTER_ACTOR_H_INCLUDED

#include "Actor.h"

enum STATUS
{
	NONE,
	PUMPED,
	DEAD
};

class MonsterActor : public Actor
{
public:
	MonsterActor(int posX, int posY);

	void initMonsterActor();

	void UpdateActor(const GameState& gameState) override;
	void DrawActor(const GameState& gameState) override;

	STATUS getStatus() const;

protected:
	STATUS m_status		= STATUS::NONE;

	static bool m_initialized;
	static Texture2D alive;
	static Texture2D pumped;
	static Texture2D dead;

	void beAttacked();
};

#endif // !MONSTER_ACTOR_H_INCLUDED