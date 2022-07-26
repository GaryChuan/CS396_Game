#pragma once

using BulletArchetype = std::tuple<Position, Velocity, Bullet, GridCell>;
using PlayerArchetype = std::tuple<Position, Velocity, Health, GridCell, RenderDetails, PlayerTag>;
using ParticleArchetype = std::tuple<Position, Velocity, Timer, RenderDetails, ParticleTag>;