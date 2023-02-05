#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED

struct SeedSpecifier
{
	int seedX;
	int seedY;
};

class Level
{
public:
	Level(int gameUnits,
		unsigned int playerX, unsigned int playerY,
		unsigned int monsterX, unsigned int monsterY);

	Level(int gameUnits,
		unsigned int playerX, unsigned int playerY,
		unsigned int monsterX, unsigned int monsterY,
		SeedSpecifier *seeds, int nSeeds);

	int getGameUnits() const;

	unsigned int getPlayerX() const;
	unsigned int getPlayerY() const;
	unsigned int getMonsterX() const;
	unsigned int getMonsterY() const;

	int getNSeed() const;
	const SeedSpecifier& getSeed(int n) const;

protected:
	int m_gameUnits;

	unsigned int playerX;
	unsigned int playerY;
	unsigned int monsterX;
	unsigned int monsterY;

	SeedSpecifier	*m_seeds;
	int				m_nSeeds = 0;
};

#endif // !LEVEL_H_INCLUDED