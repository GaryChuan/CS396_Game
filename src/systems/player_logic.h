#pragma once

struct PlayerLogic : xecs::system::instance
{
public:
	constexpr static auto typedef_v
		= xecs::system::type::update
		{
			.m_pName = "PlayerLogic"
		};

	PlayerLogic(xecs::game_mgr::instance& gameMgr)
		: xecs::system::instance { gameMgr }
	{
	}


	using query = std::tuple
		<
			xecs::query::must<PlayerTag>,
			xecs::query::none_of<Bullet>
		>;

	void OnGameStart() noexcept
	{
		mBulletArchetypePtr = &getOrCreateArchetype<BulletArchetype>();

		// Create player
		auto& playerArchetype = getOrCreateArchetype<PlayerArchetype>();

		playerArchetype.CreateEntity([&](Position& pos, Velocity& vel, Health& health, GridCell& gridCell)
			{
				pos.mValue = xcore::vector2{ 512, 400 };
				vel.mValue = xcore::vector2{ 0, 0 };

				health.mValue = 100;

				gridCell = Grid::ComputeGridCellFromWorldPosition(pos.mValue);
			});
		
	}

	__inline void operator()(const Position& pos, const Health& health)
	{
	}

private:
	xecs::archetype::instance* mBulletArchetypePtr{};
};