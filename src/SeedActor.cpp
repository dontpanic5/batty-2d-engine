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
	
}

void SeedActor::DrawActor(const GameState& gameState)
{
	float scale = (float)gameState.getUnitSzPx() / (float)seed.height;
	DrawTextureEx(
		seed,
		{ (float)gameState.unitToDirtSpaceX(m_posX), (float)gameState.unitToDirtSpaceY(m_posY) },
		0.0f, scale, WHITE);
}
