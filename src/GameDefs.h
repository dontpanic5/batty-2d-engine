#ifndef GAMEDEFS_H_INCLUDED
#define GAMEDEFS_H_INCLUDED

constexpr int SCREEN_WIDTH		= 520;
constexpr int TREE_HEIGHT		= 276;
constexpr int SCREEN_HEIGHT		= SCREEN_WIDTH + TREE_HEIGHT;

constexpr int MAX_GAME_UNITS	= 20;

//#define DEBUG
#ifdef DEBUG
#define DRAW_GRID
#define LEVEL_SKIP 10
#endif // DEBUG


enum DIRECTION
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	DIR_NONE
};

#endif // !GAMEDEFS_H_INCLUDED
