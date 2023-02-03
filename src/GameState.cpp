#include "GameDefs.h"
#include "GameState.h"

GameState::GameState()
	: player(screenWidth/2, screenHeight/2), circle(0, 0)
{
}

void GameState::init()
{
	player.initPlayerActor();
}

void GameState::update()
{
	player.UpdateActor(*this);
	circle.UpdateActor(*this);
}

void GameState::draw()
{
	player.DrawActor();
	circle.DrawActor();
}

const PlayerActor& GameState::getPlayer() const
{
	return player;
}
