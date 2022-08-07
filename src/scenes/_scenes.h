#pragma once

class Game;

enum struct GameState
{
	RUN,
	LOAD,
	UNLOAD
};

enum struct SceneState
{
	MAIN_MENU,
	GAME
};

#include "scene.h"
#include "main_menu_scene.h"
#include "game_scene.h"
