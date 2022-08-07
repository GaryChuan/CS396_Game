#pragma once

struct SpawnZombieWaveOnTimerEnd : xecs::system::instance
{
	constexpr static auto typedef_v
		= xecs::system::type::notify_moved_out
		{
			.m_pName = "SpawnZombieWaveOnTimerEnd"
		};

	using query = std::tuple
		<
			xecs::query::must<Timer, SpawnZombieWaveDetails>
		>;

	SpawnZombieWaveOnTimerEnd(xecs::game_mgr::instance& gameMgr)
		: xecs::system::instance{ gameMgr }
	{
	}

	__inline void OnGameStart()
	{
		mZombieArchetypePtr = &getOrCreateArchetype<ZombieArchetype>();
	}

	__inline void operator ()(
		xecs::component::entity& entity, 
		const SpawnZombieWaveDetails& zombieWaveDetails) noexcept
	{
		SpawnZombies(zombieWaveDetails.mID);
		
		// Delete timer entity
		DeleteEntity(entity);
	}

private:

	void SpawnZombies(int zombieWaveID)
	{
		constexpr xcore::vector2 center{ Grid::MAX_RESOLUTION_WIDTH / 2, Grid::MAX_RESOLUTION_HEIGHT / 2 };

		constexpr float outerRadius = Grid::MAX_RESOLUTION_WIDTH / 2.f;
		constexpr float innerRadius = outerRadius - 50.f;

		mZombieArchetypePtr->CreateEntities(mZombieToSpawn,
			[&](
				Position& pos,
				Colour& colour,
				Scale& scale,
				Velocity& vel,
				Health& health,
				GridCell& gridCell,
				ZombieDetails& zombieDetails,
				ZombieWave& zombieGroup,
				Zombie& zombie) noexcept
			{
				const auto angle = Math::UniformRand(0.f, Math::PI<float> * 2.f);
				const auto radius = Math::UniformRand(outerRadius, innerRadius);

				pos.mValue.m_X = center.m_X + std::cosf(angle) * radius;
				pos.mValue.m_Y = center.m_Y + std::sinf(angle) * radius;

				gridCell = Grid::ComputeGridCellFromWorldPosition(pos.mValue);

				zombieGroup.mID = zombieWaveID;

				zombieDetails.mMaxHealth		= 11.f;
				zombieDetails.mMaxSpeed			= 0.5f;
				zombieDetails.mMaxAcceleration	= 2.f;

				health.mValue = zombieDetails.mMaxHealth;

				colour.mValue = ZOMBIE_BASE_COLOUR;
				scale.mValue = xcore::vector2{ 3 , 3 };
			});

		mZombieToSpawn = 10 + std::powf(2, zombieWaveID);
	}

private:
	int mZombieToSpawn = 1;
	xecs::archetype::instance* mZombieArchetypePtr{};
};