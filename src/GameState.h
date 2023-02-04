#ifndef GAME_STATE_H_INCLUDED
#define GAME_STATE_H_INCLUDED

#include "PlayerActor.h"
#include "MonsterActor.h"

#include "GameDefs.h"

struct pos
{
	int x;
	int y;
};

enum DIRECTION
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

enum GameType
{
	GT_PLAYER,
	GT_MONSTER,
	GT_ROOT,
	GT_TUNNEL, // TODO not yet used
	GT_NONE
};

class GameState
{
public:
	GameState();

	void init();

	void update();
	void draw();

	const PlayerActor& getPlayer() const;

	bool moveIfAvailable(pos& curPos, DIRECTION dir, GameType me, GameType *obstacleHit) const;

protected:
	PlayerActor player;

	MonsterActor monster;

	bool m_dirt[GAME_UNITS][GAME_UNITS];

	bool m_roots[GAME_UNITS][GAME_UNITS];

	pos m_rootTips[GAME_UNITS * GAME_UNITS];
	unsigned int m_nRootTips = 0;

	unsigned int moveCounter = 0;

	void growRoots();

	pos closestRootToPlayer();
};

#endif // !GAME_STATE_H_INCLUDED
