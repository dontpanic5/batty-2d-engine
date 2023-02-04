#include "GameDefs.h"
#include "GameState.h"
#include <math.h>

pos moveInDir(pos pos, DIRECTION dir);

GameState::GameState()
	: player(GAME_UNITS/2, GAME_UNITS /2), monster(1, GAME_UNITS / 2)
{
	for (int i = 0; i < GAME_UNITS; i++)
	{
		for (int j = 0; j < GAME_UNITS; j++)
		{
			m_dirt[i][j] = true;
		}
	}

	for (int i = 0; i < GAME_UNITS; i++)
	{
		for (int j = 0; j < GAME_UNITS; j++)
		{
			m_roots[i][j] = false;
		}
	}
}

void GameState::init()
{
	player.initPlayerActor();
	monster.initMonsterActor();
}

void GameState::update()
{
	player.UpdateActor(*this);
	m_dirt[player.getPosX()][player.getPosY()] = false;

	if (player.playerMoved())
	{
		growRoots();

		monster.UpdateActor(*this);
	}

	if (monster.getStatus() == STATUS::DEAD /* || */)
	{
		// TODO add player kill condition
		
		// level over
	}
}

void GameState::draw()
{
	for (int i = 0; i < GAME_UNITS; i++)
	{
		for (int j = 0; j < GAME_UNITS; j++)
		{
			if (m_dirt[i][j])
			{
				DrawRectangle(unitToDirtSpaceX(i) - 1, unitToDirtSpaceY(j) -1, UNIT_SIZE_PX + 2, UNIT_SIZE_PX + 2, BROWN);
			}
		}
	}

	for (int i = 0; i < GAME_UNITS; i++)
	{
		for (int j = 0; j < GAME_UNITS; j++)
		{
			if (m_roots[i][j])
			{
				DrawRectangle(unitToDirtSpaceX(i) - 1, unitToDirtSpaceY(j) - 1, UNIT_SIZE_PX + 2, UNIT_SIZE_PX + 2, DARKBROWN);
			}
		}
	}

	monster.DrawActor();

	player.DrawActor();
}

const PlayerActor& GameState::getPlayer() const
{
	return player;
}

void GameState::growRoots()
{
	// TODO TIPS CAN GROW ANYWHERE

	if (moveCounter == 0)
	{
		//m_rootTips[0] = { GAME_UNITS / 2, 0 };
		m_roots[GAME_UNITS / 2][0] = true;
	}
	/*else if (moveCounter == 1)
	{
		moveIfAvailable(m_rootTips[0], DOWN);
		m_roots[m_rootTips[0].x][m_rootTips[0].y] = true;
	}
	else if (moveCounter == 2)
	{
		int diffX = player.getPosX() - m_rootTips[0].x;
		int diffY = player.getPosY() - m_rootTips[0].y;
		if (abs(diffY) > abs(diffX))
		{
			moveIfAvailable(m_rootTips[0], diffY > 0 ? DOWN : UP);
		}
		else
		{
			moveIfAvailable(m_rootTips[0], diffX > 0 ? RIGHT : LEFT);
		}

		m_roots[m_rootTips[0].x][m_rootTips[0].y] = true;
	}
	else
	{

	}*/
	else
	{
		pos closestRoot = closestRootToPlayer();

		pos diff = { player.getPosX() - closestRoot.x, player.getPosY() - closestRoot.y };

		DIRECTION dir;
		if (abs(diff.x) > abs(diff.y))
		{
			if (diff.x > 0)
			{
				dir = RIGHT;
			}
			else
			{
				dir = LEFT;
			}
		}
		else
		{
			if (diff.y > 0)
			{
				dir = DOWN;
			}
			else
			{
				dir = UP;
			}
		}

		pos newRoot = moveInDir(closestRoot, dir);
		m_roots[newRoot.x][newRoot.y] = true;
	}

	moveCounter++;
}

bool GameState::moveIfAvailable(pos& curPos, DIRECTION dir, GameType me, GameType *obstacleHit) const
{
	pos movedPos = moveInDir(curPos, dir);
	if (movedPos.x < 0 || movedPos.y < 0 || movedPos.x >= GAME_UNITS || movedPos.y >= GAME_UNITS)
		return false;
	if ((me == GameType::GT_ROOT || me == GameType::GT_PLAYER) && m_roots[movedPos.x][movedPos.y] == true)
	{
		*obstacleHit = GT_ROOT;
		return false;
	}
	else if (me == GameType::GT_PLAYER && monster.getPosX() == movedPos.x && monster.getPosY() == movedPos.y)
	{
		*obstacleHit = GT_MONSTER;
		return false;
	}
	else
	{
		curPos = movedPos;
		return true;
	}
}

pos moveInDir(pos pos, DIRECTION dir)
{
	if (dir == UP)
	{
		pos.y--;
	}
	else if (dir == DOWN)
	{
		pos.y++;
	}
	else if (dir == RIGHT)
	{
		pos.x++;
	}
	else if (dir == LEFT)
	{
		pos.x--;
	}

	return pos;
}

pos GameState::closestRootToPlayer()
{
	bool foundRoot = false;
	pos closest;

	for (int i = 0; i < GAME_UNITS; i++)
	{
		for (int j = 0; j < GAME_UNITS; j++)
		{
			if (m_roots[i][j])
			{
				if (!foundRoot)
				{
					closest = {i, j};
					foundRoot = true;
				}
				else
				{
					Vector2 curDiff		= { player.getPosX() - i, player.getPosY() - j};
					Vector2 closestDiff	= { player.getPosX() - closest.x, player.getPosY() - closest.y };

					float curLength		= Vector2Length(curDiff);
					float closestLength	= Vector2Length(closestDiff);

					if (curLength < closestLength)
					{
						closest = {i, j};
					}
				}
			}
		}
	}

	return closest;
}