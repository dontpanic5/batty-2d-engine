#include "GameDefs.h"
#include "GameState.h"
#include <math.h>
#include "Level.h"
#include "screens.h"

pos moveInDir(pos pos, DIRECTION dir);

GameState::GameState(Level *level, int nLevels)
	: m_curLevel(level), m_nLevels(nLevels),
	player(level[0].getPlayerX(), level[0].getPlayerY()),
	monster(level[0].getMonsterX(), level[0].getMonsterY())//,
	//m_nSeeds(level[0].getNSeed())
{
	/*if (level->getNSeed())
	{
		for (int i = 0; i < level->getNSeed(); i++)
		{
			//seeds[i] = SeedActor(level->getSeed(i).seedX, level->getSeed(i).seedY);
		}
	}*/

	reset();
}

void GameState::init()
{
	player.initPlayerActor();
	monster.initMonsterActor();
	//seeds[0].initSeedActor();
}

void GameState::update()
{
	float played = GetMusicTimePlayed(music);
	if (played > m_musicStopTime)
	{
		PauseMusicStream(music);
	}

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
		// next level or done

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
		m_started = true;

		playMusic();

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
			if (m_roots[i][j] == RS_FILLED)
			{
				DrawRectangle(
					unitToDirtSpaceX(i) - 1,
					unitToDirtSpaceY(j) - 1,
					getUnitSzPx() + 2,
					getUnitSzPx() + 2,
					DARKBROWN);
			}
			else if (m_roots[i][j] == RS_HALF)
			{
				DrawRectangleGradientV(
					unitToDirtSpaceX(i) - 1,
					unitToDirtSpaceY(j) - 1,
					getUnitSzPx() + 2,
					getUnitSzPx() + 2,
					DARKBROWN,
					BLACK);
			}
		}
	}

	/*for (int i = 0; i < m_nSeeds; i++)
	{
		seeds[i].DrawActor(*this);
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
	else if (!m_started)
	{
		DrawText("CLICK ON SCREEN TO START.", 10, 300, 22, MAROON);
		DrawText("USE ARROW KEYS TO MOVE.", 10, 340, 22, MAROON);
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

void GameState::playMusic()
{
	float played = GetMusicTimePlayed(music);
	if (!m_startedMusic)
	{
		PlayMusicStream(music);
		m_startedMusic = true;
		m_musicStopTime = 5;
	}
	else if (!IsMusicStreamPlaying(music))
	{
		PlayMusicStream(music);
		m_musicStopTime = played + 5;
	}
	else
	{
		float timeLeft = m_musicStopTime - played;
		float toAdd = 5 - timeLeft;
		m_musicStopTime += toAdd;
	}
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
			m_roots[i][j] = RS_NONE;
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

void growRoots2(GameState gameState)
{

}

void GameState::growRoots()
{
	if (moveCounter == 0)
	{
		//m_rootTips[0] = { m_curLevel.getGameUnits() / 2, 0 };
		m_roots[m_curLevel->getGameUnits() / 2][0] = RS_FILLED;
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

		if (m_roots[closestRoot.x][closestRoot.y] == RS_HALF)
		{
			m_roots[closestRoot.x][closestRoot.y] = RS_FILLED;
		}
		else
		{
			pos diff = { player.getPosX() - closestRoot.x, player.getPosY() - closestRoot.y };

			DIRECTION dirOptions[4] = {DIR_NONE, DIR_NONE, DIR_NONE, DIR_NONE};
			if (abs(diff.x) > abs(diff.y))
			{
				if (diff.x > 0)
				{
					dirOptions[0] = RIGHT;
					if (diff.y > 0)
					{
						dirOptions[1] = DOWN;
					}
					else if (diff.y < 0)
					{
						dirOptions[1] = UP;
					}
					else
					{
						dirOptions[1] = DOWN;
						dirOptions[2] = UP;
					}
				}
				else if (diff.x < 0)
				{
					dirOptions[0] = LEFT;
					if (diff.y > 0)
					{
						dirOptions[1] = DOWN;
					}
					else if (diff.y < 0)
					{
						dirOptions[1] = UP;
					}
					else
					{
						dirOptions[1] = DOWN;
						dirOptions[2] = UP;
					}
				}
			}
			else if (abs(diff.x) < abs(diff.y))
			{
				if (diff.y > 0)
				{
					dirOptions[0] = DOWN;
					if (diff.x > 0)
					{
						dirOptions[1] = RIGHT;
					}
					else if (diff.x < 0)
					{
						dirOptions[1] = LEFT;
					}
					else
					{
						dirOptions[1] = LEFT;
						dirOptions[2] = RIGHT;
					}
				}
				else if (diff.y < 0)
				{
					dirOptions[0] = UP;
					if (diff.x > 0)
					{
						dirOptions[1] = RIGHT;
					}
					else if (diff.x < 0)
					{
						dirOptions[1] = LEFT;
					}
					else
					{
						dirOptions[1] = LEFT;
						dirOptions[2] = RIGHT;
					}
				}
			}
			else
			{
				if (diff.x > 0)
				{
					dirOptions[0] = RIGHT;
					if (diff.y > 0)
					{
						dirOptions[1] = DOWN;
					}
					else if (diff.y < 0)
					{
						dirOptions[1] = UP;
					}
				}
				else
				{
					dirOptions[0] = LEFT;
					if (diff.y > 0)
					{
						dirOptions[1] = DOWN;
					}
					else if (diff.y < 0)
					{
						dirOptions[1] = UP;
					}
				}
			}

			GameType obstacle = GT_NONE;
			bool success = false;
			int i = 0;
			do
			{
				success = moveIfAvailable(closestRoot, dirOptions[i++], GT_ROOT, &obstacle);
			} while (!success && dirOptions[i] != DIR_NONE);
			if (obstacle == GT_TUNNEL)
				m_roots[closestRoot.x][closestRoot.y] = RS_HALF;
			else
				m_roots[closestRoot.x][closestRoot.y] = RS_FILLED;
		}
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
	if ((me == GameType::GT_ROOT || me == GameType::GT_PLAYER) && m_roots[movedPos.x][movedPos.y] == RS_FILLED)
	{
		*obstacleHit = GT_ROOT;
		return false;
	}
	else if ((me == GameType::GT_PLAYER || me == GT_ROOT) && monster.getPosX() == movedPos.x && monster.getPosY() == movedPos.y)
	{
		*obstacleHit = GT_MONSTER;
		return false;
	}
	else if (me == GT_ROOT && !m_dirt[movedPos.x][movedPos.y])
	{
		*obstacleHit = GT_TUNNEL;
		curPos = movedPos;
		return true;
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
			if (m_roots[i][j] == RS_FILLED || m_roots[i][j] == RS_HALF)
			{
				if (!foundRoot)
				{
					closest = {i, j};
					foundRoot = true;
				}
				else
				{
					Vector2 curDiff		= { (float)(player.getPosX() - i), (float)(player.getPosY() - j)};
					Vector2 closestDiff	= { (float)(player.getPosX() - closest.x), (float)(player.getPosY() - closest.y) };

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