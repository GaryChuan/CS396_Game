/******************************************************************************
filename: _components_archetypes.h
author: Gary Chuan gary.chuan@digipen.edu
Project: CS396 Final Project
Description:
  This file contains the declaration of all relevant
  component archetypes.
******************************************************************************/
#pragma once

using BulletArchetype = std::tuple<Position, Velocity, Bullet, Timer, GridCell>;
using ZombieArchetype = std::tuple<Position, Velocity, Health, GridCell, Zombie, Colour, Scale, ZombieDetails, ZombieWave>;
using PlayerArchetype = std::tuple<Position, Velocity, Health, Weapon, Text, GridCell, Colour, Scale, PlayerTag>;
using ParticleArchetype = std::tuple<Position, Velocity, Timer, Colour, Scale, ParticleTag>;
using ZombieWaveSpawnTimerArchetype = std::tuple<Position, Timer, Text, SpawnZombieWaveDetails>;

using ButtonArchetype = std::tuple<Position, Colour, Scale, Text, Button, ButtonDetails>;