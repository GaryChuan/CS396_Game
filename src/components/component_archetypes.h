#pragma once

using BulletArchetype = std::tuple<Position, Velocity, Bullet, GridCell>;
using PlayerArchetype = std::tuple<Position, Velocity, Health, GridCell, PlayerTag>;