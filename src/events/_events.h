/******************************************************************************
filename: _events.h
author: Gary Chuan gary.chuan@digipen.edu
Project: CS396 Final Project
Description:
  This file contains the includes of all relevant event header files.
  It also includes the declaration of Keys type which is used to keep
  track of all keyboard inputs.
******************************************************************************/
#pragma once

// keyboard input
using Keys = std::array<std::uint8_t, 0xff + 1>;

#include "on_key_triggered.h"
#include "on_key_down.h"
#include "on_key_up.h"
#include "on_mouse_left_clicked.h"
#include "on_mouse_left_held.h"
#include "on_mouse_left_released.h"
#include "on_mouse_right_click.h"
#include "on_mouse_move.h"
#include "play_sound.h"