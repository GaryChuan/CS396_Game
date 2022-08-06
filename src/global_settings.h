#pragma once

// Delta Time
constexpr static float F_DT = 1 / 60.0f;

// Zombie hit effect
constexpr static xcore::vector3 ZOMBIE_BASE_COLOUR{0, 1, 0};
constexpr static xcore::vector3 ZOMBIE_HIT_COLOUR{1, 0, 0};
constexpr static float ZOMBIE_HIT_TIMER{ 0.15f };