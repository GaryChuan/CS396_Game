#pragma once

struct BulletLogic : xecs::system::instance
{
public:
	constexpr static auto typedef_v
		= xecs::system::type::update
	{
		.m_pName = "BulletLogic"
	};

	BulletLogic(xecs::game_mgr::instance& gameMgr)
		: xecs::system::instance{ gameMgr }
	{
	}


	using query = std::tuple
		<
			xecs::query::must<Bullet>
		>;

	void OnGameStart() noexcept
	{
		mBulletArchetypePtr = &getOrCreateArchetype<BulletArchetype>();
		
		mQueryZombie.m_Must.AddFromComponents<Position, Zombie>();
		mQueryZombie.m_NoneOf.AddFromComponents<PlayerTag>();
	}

	__inline void operator()(
		xecs::component::entity& entity, 
		const Position& bulletPos, 
		const Bullet& bullet)
	{
		// Destroy if out of bounds
		if (bulletPos.x < 0 || bulletPos.x >= Grid::MAX_RESOLUTION_WIDTH 
		 || bulletPos.y < 0 || bulletPos.y >= Grid::MAX_RESOLUTION_HEIGHT)
		{
			mBulletArchetypePtr->DestroyEntity(entity);
			return;
		}
		
		Foreach(Search(mQueryZombie), 
			[&](xecs::component::entity& entity2, const Position& zombiePos) constexpr noexcept
			{
				if (entity2.isZombie() || entity == entity2)
				{
					return false;
				}

				constexpr auto distanceSq = 4 * 4;

				if ((zombiePos.mValue - bulletPos.mValue).getLengthSquared() < distanceSq)
				{
					DeleteEntity(entity);
					DeleteEntity(entity2);
					return true;
				}

				return false;
			});

		/*for (std::int16_t y = 0; y < Grid::CELL_ROW_COUNT; ++y)
		{
			for (std::int16_t x = 0; x < Grid::CELL_ROW_COUNT; ++x)
			{
				auto shareFilterPtr = findShareFilter(GridCell{ x, y });

				if (shareFilterPtr == nullptr)
				{
					continue;
				}

				Grid::Search(
					*this, *shareFilterPtr, x, y, mQueryZombie,
					[&](xecs::component::entity& entity2, const Position& zombiePos) constexpr noexcept
					{
						if (entity2.isZombie() || entity == entity2)
						{
							return false;
						}

						constexpr auto distanceSq = 4 * 4;

						if ((zombiePos.mValue - bulletPos.mValue).getLengthSquared() < distanceSq)
						{
							DeleteEntity(entity);
							DeleteEntity(entity2);
							return true;
						}

						return false;
					});
			}
		}*/
	}

private:
	xecs::archetype::instance* mBulletArchetypePtr{};
	xecs::query::instance mQueryZombie{};
};