/******************************************************************************
filename: _scenes.h
author: Gary Chuan gary.chuan@digipen.edu
Project: CS396 Final Project
Description:
  This file contains the includes of all relevant scene header files.
  It also includes the definition of the game state that determines if
  the game is running/loading/unloading.
******************************************************************************/
#pragma once

enum struct GameState
{
	RUN,
	LOAD,
	UNLOAD
};

#include "scene.h"
#include "main_menu_scene.h"
#include "game_scene.h"
#include "retry_menu_scene.h"
