#ifndef GAME_STATE_H_INCLUDED
#define GAME_STATE_H_INCLUDED

#include "PlayerActor.h"
#include "CircleActor.h"

class GameState
{
public:
	GameState();

	void update();
	void draw();

	const PlayerActor& getPlayer() const;

protected:
	PlayerActor player;

	CircleActor circle;
};

#endif // !GAME_STATE_H_INCLUDED
