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

	using StartSpawnTimer = xecs::event::instance<int>;

	using events = std::tuple<StartSpawnTimer>;

	using query = std::tuple
		<
			xecs::query::must<ZombieGroup, xecs::component::share_as_data_exclusive_tag>
		>;

	__inline void OnGameStart() noexcept
	{
		// SendEventFrom<StartTimer>(this);
		SendEventFrom<StartSpawnTimer>(this, mCurrentWave);
	}

	__inline void operator()(
		const ZombieGroup& zombieGroup,
		const xecs::component::share_filter& shareFilter)
	{
		if (zombieGroup.mID < mCurrentWave)
		{
			return;
		}

		int nZombies = 0;

		for (auto& archetypeCell : shareFilter.m_lEntries)
			for (auto& family : archetypeCell.m_lFamilies)
				nZombies += static_cast<int>(family->m_DefaultPool.Size());

		if (nZombies == 0)
		{
			SendEventFrom<StartSpawnTimer>(this, ++mCurrentWave);
		}
	}

private:
	int mCurrentWave{};
};