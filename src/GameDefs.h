#ifndef GAMEDEFS_H_INCLUDED
#define GAMEDEFS_H_INCLUDED

constexpr int SCREEN_WIDTH	= 520;
constexpr int TREE_HEIGHT	= 276;
constexpr int SCREEN_HEIGHT	= SCREEN_WIDTH + TREE_HEIGHT;

constexpr unsigned int GAME_UNITS = 6;

int unitToDirtSpaceX(int unit);
int unitToDirtSpaceY(int unit);

constexpr unsigned int UNIT_SIZE_PX = SCREEN_WIDTH / GAME_UNITS;

#endif // !GAMEDEFS_H_INCLUDED
