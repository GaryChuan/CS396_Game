/******************************************************************************
filename: _systems.h
author: Gary Chuan gary.chuan@digipen.edu
Project: CS396 Final Project
Description:
  This file contains the includes of all relevant system files.
******************************************************************************/
#pragma once

// Movement
#include "update_movement.h"
#include "clamp_movement.h"

// Particles
#include "update_particles.h"

// Logic
#include "player_logic.h"
#include "button_logic.h"
#include "bullet_logic.h"
#include "zombie_logic.h"
#include "zombie_attack_logic.h"
#include "zombie_steering_logic.h"
#include "zombie_update_velocity.h"
#include "zombie_wave_logic.h"
#include "zombie_wave_spawn_timer_logic.h"

// Timer
#include "update_timer.h"

// Game Events
#include "spawn_particle_on_zombie_death.h"
#include "spawn_particle_on_zombie_hit.h"
#include "destroy_particle_on_remove_timer.h"
#include "destroy_bullet_on_remove_timer.h"
#include "player_deactivate_text_on_remove_timer.h"
#include "start_timer_on_zombie_wave_cleared.h"
#include "spawn_zombie_wave_on_timer_end.h"
#include "zombie_restore_colour_on_remove_timer.h"

// Sound Events
#include "on_play_sound.h"
#include "play_sound_on_zombie_dead.h";

// Input Events
#include "player_input_on_key_triggered.h"
#include "player_input_on_key_down.h"
#include "player_input_on_key_up.h"
#include "player_input_on_mouse_left_clicked.h"
#include "player_input_on_mouse_left_held.h"
#include "player_input_on_mouse_left_released.h"
#include "button_on_mouse_move.h"
#include "button_on_left_mouse_clicked.h"
#include "button_on_left_mouse_released.h"

// Renderer
#include "renderer.h"
#include "render_player.h"
#include "render_zombies.h"
#include "render_bullets.h"
#include "render_particles.h"
#include "render_text.h"
#include "render_buttons.h"
#include "render_grid.h"