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

	void UpdateActor(const GameState& gameState) override;
	void DrawActor() override;

	STATUS getStatus() const;

protected:
	STATUS m_status = STATUS::NONE;

	void beAttacked();
};

#endif // !MONSTER_ACTOR_H_INCLUDED