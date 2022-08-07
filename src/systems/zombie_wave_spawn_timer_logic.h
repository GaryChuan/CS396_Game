/******************************************************************************
filename: zombie_wave_spawn_timer_logic.h
author: Gary Chuan gary.chuan@digipen.edu
Project: CS396 Final Project
Description:
  This file contains the definition of ZombieWaveSpawnTimerLogic system
  where it updates the timer till the next zombie wave spawns.
******************************************************************************/
#pragma once

struct ZombieWaveSpawnTimerLogic : xecs::system::instance
{
public:
	constexpr static auto typedef_v
		= xecs::system::type::update
	{
		.m_pName = "ZombieWaveSpawnTimerLogic"
	};

	ZombieWaveSpawnTimerLogic(xecs::game_mgr::instance& gameMgr)
		: xecs::system::instance{ gameMgr }
	{
	}

	using query = std::tuple
		<
			xecs::query::must<Text, Timer, SpawnZombieWaveDetails>
		>;

	__inline void OnGameStart() noexcept
	{
		// SendEventFrom<StartTimer>(this);
	}

	__inline void operator()(Text& text, SpawnZombieWaveDetails& waveDetails, const Timer& timer)
	{
		int timerValue = timer.mValue;

		if (timerValue == 0)
		{
			text.mOffset.mValue = xcore::vector2{ -30, 0 };
			text.mValue = "Wave ";
			text.mValue += std::to_string(waveDetails.mID + 1);
		}
		else
		{
			text.mValue = std::to_string(timerValue);
		}
	}
};