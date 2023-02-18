/**********************************************************************************************
*
*   raylib - Advance Game template
*
*   Gameplay Screen Functions Definitions (Init, Update, Draw, Unload)
*
*   Copyright (c) 2014-2022 Ramon Santamaria (@raysan5)
*
*   This software is provided "as-is", without any express or implied warranty. In no event
*   will the authors be held liable for any damages arising from the use of this software.
*
*   Permission is granted to anyone to use this software for any purpose, including commercial
*   applications, and to alter it and redistribute it freely, subject to the following restrictions:
*
*     1. The origin of this software must not be misrepresented; you must not claim that you
*     wrote the original software. If you use this software in a product, an acknowledgment
*     in the product documentation would be appreciated but is not required.
*
*     2. Altered source versions must be plainly marked as such, and must not be misrepresented
*     as being the original software.
*
*     3. This notice may not be removed or altered from any source distribution.
*
**********************************************************************************************/

#include "raylib.h"
#include "screens.h"
#include "GameDefs.h"
#include "GameState.h"
#include "AnimationMgr.h"
#include "Level.h"

//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
static int framesCounter = 0;
static int finishScreen = 0;

constexpr unsigned int NUM_LEVELS = 9;

SeedSpecifier level10Seeds[1] = {{5, 5}};

Level levels[NUM_LEVELS] =
{
    Level(6, 4, 3, 1, 3),
    Level(6, 3, 0, 1, 3),
    Level(6, 5, 2, 0, 5),
    Level(6, 5, 1, 0, 5),
    Level(6, 5, 0, 0, 3),
    Level(6, 5, 0, 0, 2),
    Level(6, 5, 0, 0, 1),
    Level(6, 5, 0, 0, 0),
    Level(6, 5, 2, 0, 0)//,
    //Level(6, 4, 3, 1, 3, level10Seeds, 1)
};

#ifdef LEVEL_SKIP
GameState gameState(levels + LEVEL_SKIP - 1, NUM_LEVELS);
#else // LEVEL_SKIP
GameState gameState(levels, NUM_LEVELS);
#endif

Texture2D tree;

//----------------------------------------------------------------------------------
// Gameplay Screen Functions Definition
//----------------------------------------------------------------------------------

// Gameplay Screen Initialization logic
void InitGameplayScreen(void)
{
    // TODO: Initialize GAMEPLAY screen variables here!
    framesCounter = 0;
    finishScreen = 0;

    gameState.init();

    tree = LoadTexture("resources/tree.png");
}

// Gameplay Screen Update logic
void UpdateGameplayScreen(void)
{
    // TODO: Update GAMEPLAY screen variables here!

    gameState.update();

    // Press enter or tap to change to ENDING screen
    /*if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
    {
        finishScreen = 1;
        PlaySound(dig);
    }*/
}

// Gameplay Screen Draw logic
void DrawGameplayScreen(void)
{
    //background
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLACK);

    //Vector2 pos = { 20, 10 };
    //DrawTextEx(font, "GAMEPLAY SCREEN", pos, font.baseSize*3.0f, 4, MAROON);

    DrawTexture(tree, 0, 0, WHITE);

    gameState.draw();

    //DrawText("PRESS ENTER or TAP to JUMP to ENDING SCREEN", 130, 220, 20, MAROON);
}

// Gameplay Screen Unload logic
void UnloadGameplayScreen(void)
{
    // TODO: Unload GAMEPLAY screen variables here!
}

// Gameplay Screen should finish?
int FinishGameplayScreen(void)
{
    return finishScreen;
}