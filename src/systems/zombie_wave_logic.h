/******************************************************************************
filename: zombie_wave_logic.h
author: Gary Chuan gary.chuan@digipen.edu
Project: CS396 Final Project
Description:
  This file contains the definition of ZombieWaveLogic which checks
  if current wave is cleared and is in charge of triggering an event
  to start spawning the next wave.
******************************************************************************/
#pragma once

struct ZombieWaveLogic : xecs::system::instance
{
public:
	constexpr static auto typedef_v
		= xecs::system::type::update
	{
		.m_pName = "ZombieWaveLogic"
	};

	ZombieWaveLogic(xecs::game_mgr::instance& gameMgr)
		: xecs::system::instance{ gameMgr }
	{
	}

	using StartSpawnTimer = xecs::event::instance<int>;

	using events = std::tuple<StartSpawnTimer>;

	using query = std::tuple
		<
			xecs::query::must<ZombieWave, xecs::component::share_as_data_exclusive_tag>
		>;

	__inline void OnGameStart() noexcept
	{
		// SendEventFrom<StartTimer>(this);
		SendEventFrom<StartSpawnTimer>(this, mCurrentWave);
	}

	__inline void operator()(
		const ZombieWave& zombieWave,
		const xecs::component::share_filter& shareFilter)
	{
		if (zombieWave.mID < mCurrentWave)
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