/******************************************************************************
filename: start_timer_on_zombie_wave_cleared.h
author: Gary Chuan gary.chuan@digipen.edu
Project: CS396 Final Project
Description:
  This file contains the definition of StartTimerOnZombieWaveCleared
  which handles the starting of the timer when a zombie wave is cleared.
  It spawns an entity which acts as the timer.
******************************************************************************/
#pragma once

struct StartTimerOnZombieWaveCleared : xecs::system::instance
{
	constexpr static auto typedef_v
		= xecs::system::type::system_event
		<
			ZombieWaveLogic,
			ZombieWaveLogic::StartSpawnTimer
		>
		{
			.m_pName = "StartTimerOnZombieWaveCleared"
		};

	StartTimerOnZombieWaveCleared(xecs::game_mgr::instance& gameMgr)
		: xecs::system::instance{ gameMgr }
	{
	}

	__inline void OnEvent(int currentWave) noexcept
	{
		mSpawnTimerArchetypePtr = &getOrCreateArchetype<ZombieWaveSpawnTimerArchetype>();

		mSpawnTimerArchetypePtr->CreateEntity(
			[currentWave]
			(
				Position& position, 
				SpawnZombieWaveDetails& zombieWaveDetails, 
				Timer& timer, 
				Text& text
			)
			{
				position.mValue = xcore::vector2
				{
					Grid::MAX_RESOLUTION_WIDTH / 2,
					Grid::MAX_RESOLUTION_HEIGHT / 2
				};

				timer.mValue = 5.f;

				zombieWaveDetails.mID = currentWave;

				text.mFont = Text::Font::HELVETICA_18;
				text.mActive = true;
				text.mValue = '0' + timer.mValue;
			});
	}

private:
	xecs::archetype::instance* mSpawnTimerArchetypePtr{};
};