#pragma once

struct SpawnZombieGroupOnTimerEnd : xecs::system::instance
{
	constexpr static auto typedef_v
		= xecs::system::type::notify_moved_out
		{
			.m_pName = "SpawnZombieGroupOnTimerEnd"
		};

	using query = std::tuple
		<
			xecs::query::must<Timer, ZombieGroup>
		>;

	SpawnZombieGroupOnTimerEnd(xecs::game_mgr::instance& gameMgr)
		: xecs::system::instance{ gameMgr }
	{
	}

	__inline void OnGameStart()
	{
		mZombieArchetypePtr = &getOrCreateArchetype<ZombieArchetype>();
	}

	__inline void operator ()(xecs::component::entity& entity) noexcept
	{
		SpawnZombies();
		
		// Delete timer entity
		DeleteEntity(entity);
	}

private:

	void SpawnZombies()
	{
		mZombieArchetypePtr->CreateEntities(mZombieToSpawn,
			[&](
				Position& pos,
				Velocity& vel,
				Health& health,
				GridCell& gridCell,
				ZombieDetails& zombieDetails,
				RenderDetails& renderDetails,
				ZombieGroup& zombieGroup,
				Zombie& zombie) noexcept
			{
				pos.mValue = xcore::vector2
				{
					static_cast<float>(std::rand() % Grid::MAX_RESOLUTION_WIDTH),
					static_cast<float>(std::rand() % Grid::MAX_RESOLUTION_HEIGHT)
				};

				gridCell = Grid::ComputeGridCellFromWorldPosition(pos.mValue);

				zombieGroup.mID = mCurrentWave;

				zombieDetails.mMaxHealth		= 10.f;
				zombieDetails.mMaxSpeed			= 0.5f;
				zombieDetails.mMaxAcceleration	= 2.f;

				health.mValue = zombieDetails.mMaxHealth;

				renderDetails.mColour = Colour{ 0, 1, 0 };
				renderDetails.mSize = Size{ 3 , 3 };
			});

		++mCurrentWave;
		mZombieToSpawn += mCurrentWave * 2;
	}

private:
	int mZombieToSpawn = 1;
	int mCurrentWave = 0;
	xecs::archetype::instance* mZombieArchetypePtr{};
};