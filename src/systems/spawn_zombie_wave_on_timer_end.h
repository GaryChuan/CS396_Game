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
				pos.mValue = xcore::vector2
				{
					static_cast<float>(std::rand() % Grid::MAX_RESOLUTION_WIDTH),
					static_cast<float>(std::rand() % Grid::MAX_RESOLUTION_HEIGHT)
				};

				gridCell = Grid::ComputeGridCellFromWorldPosition(pos.mValue);

				zombieGroup.mID = zombieWaveID;

				zombieDetails.mMaxHealth		= 11.f;
				zombieDetails.mMaxSpeed			= 0.5f;
				zombieDetails.mMaxAcceleration	= 2.f;

				health.mValue = zombieDetails.mMaxHealth;

				colour.mValue = ZOMBIE_BASE_COLOUR;
				scale.mValue = xcore::vector2{ 3 , 3 };
			});

		mZombieToSpawn = 1 + std::powf(2, zombieWaveID);
	}

private:
	int mZombieToSpawn = 1;
	xecs::archetype::instance* mZombieArchetypePtr{};
};