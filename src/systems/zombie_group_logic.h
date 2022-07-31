#pragma once

struct ZombieGroupLogic : xecs::system::instance
{
public:
	constexpr static auto typedef_v
		= xecs::system::type::update
	{
		.m_pName = "ZombieGroupLogic"
	};

	ZombieGroupLogic(xecs::game_mgr::instance& gameMgr)
		: xecs::system::instance{ gameMgr }
	{
	}

	using query = std::tuple
		<
			xecs::query::must<ZombieGroup, xecs::component::share_as_data_exclusive_tag>
		>;

	__inline void OnGameStart() noexcept
	{
		mZombieArchetypePtr = &getOrCreateArchetype<ZombieArchetype>();
		mQueryPlayer.m_Must.AddFromComponents<PlayerTag>();

		SpawnZombies();
	}

	__inline void operator()(
		const ZombieGroup& zombieGroup, 
		const xecs::component::share_filter& shareFilter)
	{
		int nZombies = 0;

		for (const auto& archetypeCell : shareFilter.m_lEntries)
			for (const auto& family: archetypeCell.m_lFamilies)
				nZombies += static_cast<int>(family->m_DefaultPool.Size());

		std::cout << "Number of zombies : " << nZombies << std::endl;
	}

private:
	void SpawnZombies()
	{
		mZombieArchetypePtr->CreateEntities(100,
			[&](
				Position& pos,
				Velocity& vel,
				Health& health,
				GridCell& gridCell,
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

				renderDetails.mColour = Colour{ 0, 1, 0 };
				renderDetails.mSize = Size{ 3 , 3 };
			});

		++mCurrentWave;
	}

private:
	int mCurrentWave = 0;
	xecs::query::instance mQueryPlayer{};
	xecs::archetype::instance* mZombieArchetypePtr{};
};