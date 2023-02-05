#ifndef GAME_STATE_H_INCLUDED
#define GAME_STATE_H_INCLUDED

#include "PlayerActor.h"
#include "MonsterActor.h"

#include "GameDefs.h"
#include "Level.h"

struct pos
{
	int x;
	int y;
};

enum GameType
{
	GT_PLAYER,
	GT_MONSTER,
	GT_ROOT,
	GT_TUNNEL,
	GT_NONE
};

enum ROOT_STATE
{
	RS_NONE,
	RS_HALF,
	RS_FILLED
};

enum GAME_STATE_WIN_LOSE
{
	GSWL_NONE,
	GSWL_WIN,
	GSWL_LOSE,
	GSWL_END
};

class GameState
{
public:
	GameState(Level *level, int nLevels);

	void init();

	void update();
	void draw();

	const PlayerActor& getPlayer() const;

	bool moveIfAvailable(pos& curPos, DIRECTION dir, GameType me, GameType *obstacleHit) const;

	pos closestRootToPlayer() const;


	int getUnitSzPx() const;
	int unitToDirtSpaceX(int unit) const;
	int unitToDirtSpaceY(int unit) const;

protected:
	Level *m_curLevel;
	int m_curLevelIdx = 0;
	int m_nLevels;

	PlayerActor player;

	MonsterActor monster;

	bool m_dirt[MAX_GAME_UNITS][MAX_GAME_UNITS];

	ROOT_STATE m_roots[MAX_GAME_UNITS][MAX_GAME_UNITS];

	pos m_rootTips[MAX_GAME_UNITS * MAX_GAME_UNITS];
	unsigned int m_nRootTips = 0;

	unsigned int moveCounter = 0;

	GAME_STATE_WIN_LOSE m_gameStateWinLose = GSWL_NONE;

	void reset();
	void resetAll();

	void growRoots();
};

#endif // !GAME_STATE_H_INCLUDED
