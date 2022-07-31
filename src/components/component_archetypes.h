#pragma once

using BulletArchetype = std::tuple<Position, Velocity, Bullet, Timer, GridCell>;
using ZombieArchetype = std::tuple<Position, Velocity, Health, GridCell, RenderDetails, Zombie, ZombieGroup>;
using PlayerArchetype = std::tuple<Position, Velocity, Health, Weapon, Text, GridCell, RenderDetails, PlayerTag>;
using ParticleArchetype = std::tuple<Position, Velocity, Timer, RenderDetails, ParticleTag>;
using ZombieGroupSpawnTimerArchetype = std::tuple<Position, Timer, Text, ZombieGroup>;