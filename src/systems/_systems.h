#pragma once

// Movement
#include "update_movement.h"
#include "clamp_movement.h"

// Particles
#include "update_particles.h"

// Logic
#include "player_logic.h"
#include "bullet_logic.h"
#include "zombie_logic.h"
#include "zombie_group_logic.h"
#include "zombie_group_spawn_timer_logic.h"

// Timer
#include "update_timer.h"

// Game Events
#include "spawn_particle_on_zombie_death.h"
#include "destroy_particle_on_remove_timer.h"
#include "destroy_bullet_on_remove_timer.h"
#include "player_deactivate_text_on_remove_timer.h"
#include "start_timer_on_zombie_group_cleared.h"
#include "spawn_zombie_group_on_timer_end.h"

// Input Events
#include "player_input_on_key_triggered.h"
#include "player_input_on_key_down.h"
#include "player_input_on_key_up.h"
#include "player_input_on_mouse_left_clicked.h"
#include "player_input_on_mouse_left_held.h"
#include "player_input_on_mouse_left_released.h"

// Renderer
#include "renderer.h"
#include "render_player.h"
#include "render_zombies.h"
#include "render_bullets.h"
#include "render_particles.h"
#include "render_text.h"
#include "render_grid.h"