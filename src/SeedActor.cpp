#include "SeedActor.h"
#include "GameState.h"

bool		SeedActor::m_initialized = false;
Texture2D	SeedActor::seed;

SeedActor::SeedActor()
	: Actor(0, 0)
{
}

SeedActor::SeedActor(int posX, int posY)
	: Actor(posX, posY)
{
}

void SeedActor::initSeedActor()
{
	if (m_initialized == false)
	{
		seed = LoadTexture("resources/seed.png");
		m_initialized = true;
	}
}

void SeedActor::UpdateActor(const GameState& gameState)
{
		pos closestRoot = gameState.closestRootToPlayer();

		if (m_roots[closestRoot.x][closestRoot.y] == RS_HALF)
		{
			m_roots[closestRoot.x][closestRoot.y] = RS_FILLED;
		}
		else
		{
			pos diff = { player.getPosX() - closestRoot.x, player.getPosY() - closestRoot.y };

			DIRECTION dirOptions[4] = { DIR_NONE, DIR_NONE, DIR_NONE, DIR_NONE };
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

void SeedActor::DrawActor(const GameState& gameState)
{
	float scale = (float)gameState.getUnitSzPx() / (float)seed.height;
	DrawTextureEx(
		seed,
		{ (float)gameState.unitToDirtSpaceX(m_posX), (float)gameState.unitToDirtSpaceY(m_posY) },
		0.0f, scale, WHITE);
}
