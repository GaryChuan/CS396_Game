#pragma once

using BulletArchetype = std::tuple<Position, Velocity, Bullet, Timer, GridCell>;
using ZombieArchetype = std::tuple<Position, Velocity, Health, GridCell, Zombie, Colour, Scale, ZombieDetails, ZombieWave>;
using PlayerArchetype = std::tuple<Position, Velocity, Health, Weapon, Text, GridCell, Colour, Scale, PlayerTag>;
using ParticleArchetype = std::tuple<Position, Velocity, Timer, Colour, Scale, ParticleTag>;
using ZombieWaveSpawnTimerArchetype = std::tuple<Position, Timer, Text, SpawnZombieWaveDetails>;