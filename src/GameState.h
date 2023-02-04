#ifndef GAME_STATE_H_INCLUDED
#define GAME_STATE_H_INCLUDED

#include "PlayerActor.h"
#include "CircleActor.h"

#include "GameDefs.h"

class GameState
{
public:
	GameState();

	void init();

	void update();
	void draw();

	const PlayerActor& getPlayer() const;

protected:
	PlayerActor player;

	CircleActor circle;

	bool dirt[GAME_UNITS][GAME_UNITS];
};

#endif // !GAME_STATE_H_INCLUDED
