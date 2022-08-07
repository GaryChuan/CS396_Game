/******************************************************************************
filename: global_settings.h
author: Gary Chuan gary.chuan@digipen.edu
Project: CS396 Final Project
Description:
  This file contains the declaration of global variables.
******************************************************************************/

#pragma once

// Delta Time
constexpr static float F_DT = 1 / 60.0f;

// Zombie hit effect
constexpr static xcore::vector3 ZOMBIE_BASE_COLOUR{0, 1, 0};
constexpr static xcore::vector3 ZOMBIE_HIT_COLOUR{1, 0, 0};
constexpr static float ZOMBIE_HIT_TIMER{ 0.15f };

// Button colours
constexpr static xcore::vector3 BUTTON_DEFAULT_COLOUR{ 1, 1, 1 };
constexpr static xcore::vector3 BUTTON_HOVER_COLOUR{ 0.3f, 0.5f, 0.3f };
constexpr static xcore::vector3 BUTTON_PRESSED_COLOUR{ 0.1f, 0.5f, 0.1f };
constexpr static xcore::vector3 BUTTON_RELEASED_COLOUR{ 0.2f, 0.5f, 0.2f };

// Player
constexpr static float PLAYER_MAX_HEALTH = 15.f;

// Audio
constexpr static const char* PISTOL_SHOT_SOUND = "PistolShot";
constexpr static const char* BGM = "BGM";