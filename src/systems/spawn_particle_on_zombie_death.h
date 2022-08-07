/******************************************************************************
filename: spawn_particle_on_zombie_death.h
author: Gary Chuan gary.chuan@digipen.edu
Project: CS396 Final Project
Description:
  This file contains the definition of SpawnParticleOnZombieDeath which handles
  spawning of particles when a zombie is dead.
******************************************************************************/
#pragma once

struct SpawnParticleOnZombieDeath : xecs::system::instance
{
	constexpr static auto typedef_v
		= xecs::system::type::notify_destroy
		{
			.m_pName = "SpawnParticleOnZombieDeath"
		};

	using query = std::tuple
		<
			xecs::query::must<Zombie>,
			xecs::query::none_of<PlayerTag>
		>;

	SpawnParticleOnZombieDeath(xecs::game_mgr::instance& gameMgr)
		: xecs::system::instance { gameMgr }
	{
	}

	__inline void OnGameStart() noexcept
	{
		mParticleArchetype = &getOrCreateArchetype<ParticleArchetype>();
	}

	__inline void operator()(const Position& zombiePos) noexcept
	{
		constexpr float r = 0.05f;
		constexpr float g = 226.f / 255.f;
		constexpr float b = 60.f / 255.f;

		mParticleArchetype->CreateEntities(50,
			[&](Position& particlePos, Velocity& velocity, Timer& timer, Colour& colour, Scale& scale)
			{
				particlePos.mValue = zombiePos.mValue;

				velocity.mValue = Math::UniformDiskRand(2.f);

				timer.mValue = 0.75f;

				colour.mValue = xcore::vector3{ r, g, b };
				scale.mValue = xcore::vector2{ 0.5, 0.5 };
			});
	}

private:
	xecs::archetype::instance* mParticleArchetype{};
};