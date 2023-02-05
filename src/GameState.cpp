#include "GameDefs.h"
#include "GameState.h"
#include <math.h>
#include "Level.h"

pos moveInDir(pos pos, DIRECTION dir);

GameState::GameState(Level *level, int nLevels)
	: m_curLevel(level), m_nLevels(nLevels),
	player(level[0].getPlayerX(), level[0].getPlayerY()),
	monster(level[0].getMonsterX(), level[0].getMonsterY())
{
	reset();
}

void GameState::init()
{
	player.initPlayerActor();
	monster.initMonsterActor();
}

void GameState::update()
{
	if (m_gameStateWinLose == GSWL_LOSE)
	{
		if (IsKeyPressed(KEY_ENTER))
		{
			resetAll();
		}
		return;
	}
	if (m_gameStateWinLose == GSWL_WIN)
	{
		// TODO next level or done

		if (IsKeyPressed(KEY_ENTER))
		{
			if (m_curLevelIdx + 1 < m_nLevels)
			{
				// next level

				m_curLevel++;
				m_curLevelIdx++;

				resetAll();
			}
			else
			{
				m_gameStateWinLose = GSWL_END;
			}
		}

		return;
	}
	if (m_gameStateWinLose == GSWL_END)
		return;

	player.UpdateActor(*this);
	m_dirt[player.getPosX()][player.getPosY()] = false;

	if (player.playerMoved())
	{
		growRoots();

		player.UpdateDeath(*this);

		monster.UpdateActor(*this);
	}

	if (player.getStatus() == PLAYER_STATUS::PPTD_DEAD)
	{
		m_gameStateWinLose = GSWL_LOSE;
	}
	else if (monster.getStatus() == STATUS::DEAD)
	{
		m_gameStateWinLose = GSWL_WIN;
	}
}

void GameState::draw()
{
	for (int i = 0; i < m_curLevel->getGameUnits(); i++)
	{
		for (int j = 0; j < m_curLevel->getGameUnits(); j++)
		{
			if (m_dirt[i][j])
			{
				DrawRectangle(
					unitToDirtSpaceX(i) - 1,
					unitToDirtSpaceY(j) -1,
					getUnitSzPx() + 2,
					getUnitSzPx() + 2,
					BROWN);
			}
		}
	}

#ifdef DRAW_GRID
	for (int i = 0; i < m_curLevel->getGameUnits(); i++)
	{
		DrawLine(
			0,
			i * getUnitSzPx() + TREE_HEIGHT,
			SCREEN_WIDTH,
			i * getUnitSzPx() + TREE_HEIGHT,
			RED);
	}
	for (int i = 0; i < m_curLevel->getGameUnits(); i++)
	{
		DrawLine(
			i * getUnitSzPx(),
			0,
			i * getUnitSzPx(),
			SCREEN_HEIGHT,
			RED);
	}
#endif // DRAW_GRID


	for (int i = 0; i < m_curLevel->getGameUnits(); i++)
	{
		for (int j = 0; j < m_curLevel->getGameUnits(); j++)
		{
			if (m_roots[i][j])
			{
				DrawRectangle(
					unitToDirtSpaceX(i) - 1,
					unitToDirtSpaceY(j) - 1,
					getUnitSzPx() + 2,
					getUnitSzPx() + 2,
					DARKBROWN);
			}
		}
	}

	monster.DrawActor(*this);

	player.DrawActor(*this);

	if (m_gameStateWinLose == GSWL_LOSE)
	{
		DrawText("GAME OVER.", 10, 300, 22, MAROON);
		DrawText("PRESS ENTER TO RETRY.", 10, 340, 22, MAROON);
	}
	else if (m_gameStateWinLose == GSWL_WIN)
	{
		DrawText("YOU HAVE EXPLODED THE MONSTER.", 10, 300, 22, MAROON);
		DrawText("PRESS ENTER TO CONTINUE.", 10, 340, 22, MAROON);
	}
	else if (m_gameStateWinLose == GSWL_END)
	{
		DrawText("YOU HAVE EXPLODED ALL THE MONSTERS.", 10, 300, 22, MAROON);
	}
}

const PlayerActor& GameState::getPlayer() const
{
	return player;
}

int GameState::getUnitSzPx() const
{
	return SCREEN_WIDTH / m_curLevel->getGameUnits();
}

int GameState::unitToDirtSpaceX(int unit) const
{
	return SCREEN_WIDTH * unit / m_curLevel->getGameUnits();
}

int GameState::unitToDirtSpaceY(int unit) const
{
	return (SCREEN_HEIGHT - TREE_HEIGHT) * unit / m_curLevel->getGameUnits() + TREE_HEIGHT;
}

void GameState::reset()
{
	m_gameStateWinLose = GSWL_NONE;

	for (int i = 0; i < m_curLevel->getGameUnits(); i++)
	{
		for (int j = 0; j < m_curLevel->getGameUnits(); j++)
		{
			m_dirt[i][j] = true;
		}
	}

	for (int i = 0; i < m_curLevel->getGameUnits(); i++)
	{
		for (int j = 0; j < m_curLevel->getGameUnits(); j++)
		{
			m_roots[i][j] = false;
		}
	}

	moveCounter = 0;

	m_nRootTips = 0;

	// TODO reset root tips?
}

void GameState::resetAll()
{
	reset();
	player = PlayerActor(m_curLevel->getPlayerX(), m_curLevel->getPlayerY());
	monster = MonsterActor(m_curLevel->getMonsterX(), m_curLevel->getMonsterY());
}

void GameState::growRoots()
{
	// TODO TIPS CAN GROW ANYWHERE

	if (moveCounter == 0)
	{
		//m_rootTips[0] = { m_curLevel.getGameUnits() / 2, 0 };
		m_roots[m_curLevel->getGameUnits() / 2][0] = true;
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

		DIRECTION dirOptions[4] = {DIR_NONE, DIR_NONE, DIR_NONE, DIR_NONE};
		if (abs(diff.x) > abs(diff.y))
		{
			if (diff.x > 0)
			{
				dirOptions[0] = RIGHT;
			}
			else
			{
				dirOptions[0] = LEFT;
			}
		}
		else if (abs(diff.x) < abs(diff.y))
		{
			if (diff.y > 0)
			{
				dirOptions[0] = DOWN;
			}
			else
			{
				dirOptions[0] = UP;
			}
		}
		else

		GameType obstacle = GT_NONE;
		bool success = moveIfAvailable(closestRoot, dir, GT_ROOT, &obstacle);
		m_roots[closestRoot.x][closestRoot.y] = true;
	}

	moveCounter++;
}

bool GameState::moveIfAvailable(pos& curPos, DIRECTION dir, GameType me, GameType *obstacleHit) const
{
	pos movedPos = moveInDir(curPos, dir);
	if (
		movedPos.x < 0 ||
		movedPos.y < 0 ||
		movedPos.x >= m_curLevel->getGameUnits() ||
		movedPos.y >= m_curLevel->getGameUnits())
		return false;
	if ((me == GameType::GT_ROOT || me == GameType::GT_PLAYER) && m_roots[movedPos.x][movedPos.y] == true)
	{
		*obstacleHit = GT_ROOT;
		return false;
	}
	else if ((me == GameType::GT_PLAYER || me == GT_ROOT) && monster.getPosX() == movedPos.x && monster.getPosY() == movedPos.y)
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

pos GameState::closestRootToPlayer() const
{
	bool foundRoot = false;
	pos closest;

	for (int i = 0; i < m_curLevel->getGameUnits(); i++)
	{
		for (int j = 0; j < m_curLevel->getGameUnits(); j++)
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