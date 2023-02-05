#include "Level.h"

Level::Level(int gameUnits,
	unsigned int playerX, unsigned int playerY,
	unsigned int monsterX, unsigned int monsterY)
	: m_gameUnits(gameUnits),
	playerX(playerX), playerY(playerY),
	monsterX(monsterX), monsterY(monsterY)
{
}

Level::Level(int gameUnits,
	unsigned int playerX, unsigned int playerY,
	unsigned int monsterX, unsigned int monsterY,
	SeedSpecifier* seeds, int nSeeds)
	: m_gameUnits(gameUnits),
	playerX(playerX), playerY(playerY),
	monsterX(monsterX), monsterY(monsterY),
	m_seeds(seeds), m_nSeeds(nSeeds)
{
}

int Level::getGameUnits() const
{
	return m_gameUnits;
}

unsigned int Level::getPlayerX() const
{
	return playerX;
}

unsigned int Level::getPlayerY() const
{
	return playerY;
}

unsigned int Level::getMonsterX() const
{
	return monsterX;
}

unsigned int Level::getMonsterY() const
{
	return monsterY;
}

int Level::getNSeed() const
{
	return m_nSeeds;
}

const SeedSpecifier& Level::getSeed(int n) const
{
	return m_seeds[n];
}
