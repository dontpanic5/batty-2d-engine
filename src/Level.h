#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED

class Level
{
public:
	Level(int gameUnits,
		unsigned int playerX, unsigned int playerY,
		unsigned int monsterX, unsigned int monsterY);

	int getGameUnits() const;

	unsigned int getPlayerX() const;
	unsigned int getPlayerY() const;
	unsigned int getMonsterX() const;
	unsigned int getMonsterY() const;

protected:
	int m_gameUnits;

	unsigned int playerX;
	unsigned int playerY;
	unsigned int monsterX;
	unsigned int monsterY;
};

#endif // !LEVEL_H_INCLUDED