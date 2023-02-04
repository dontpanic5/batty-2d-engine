#include "GameDefs.h"

int unitToDirtSpaceX(int unit)
{
	return SCREEN_WIDTH * unit / GAME_UNITS;
}

int unitToDirtSpaceY(int unit)
{
	return (SCREEN_HEIGHT - TREE_HEIGHT)* unit / GAME_UNITS + TREE_HEIGHT;
}