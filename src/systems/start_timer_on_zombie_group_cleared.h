#pragma once

struct StartTimerOnZombieGroupCleared : xecs::system::instance
{
	constexpr static auto typedef_v
		= xecs::system::type::system_event
		<
			ZombieGroupLogic,
			ZombieGroupLogic::StartSpawnTimer
		>
		{
			.m_pName = "StartTimerOnZombieGroupCleared"
		};

	StartTimerOnZombieGroupCleared(xecs::game_mgr::instance& gameMgr)
		: xecs::system::instance{ gameMgr }
	{
	}

	__inline void OnEvent(int currentWave) noexcept
	{
		mSpawnTimerArchetypePtr = &getOrCreateArchetype<ZombieGroupSpawnTimerArchetype>();

		mSpawnTimerArchetypePtr->CreateEntity([currentWave](Position& position, ZombieGroup& group, Timer& timer, Text& text)
			{
				position.mValue = xcore::vector2
				{
					Grid::MAX_RESOLUTION_WIDTH / 2,
					Grid::MAX_RESOLUTION_HEIGHT / 2
				};


				group.mID = currentWave;

				timer.mValue = 5.f;

				text.mFont = Text::Font::HELVETICA_18;
				text.mActive = true;
				text.mValue = '0' + timer.mValue;
			});
	}

private:
	xecs::archetype::instance* mSpawnTimerArchetypePtr{};
};