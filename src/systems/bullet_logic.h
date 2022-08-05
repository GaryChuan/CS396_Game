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

	void OnGameStart() noexcept
	{
		mQueryBullets.m_Must.AddFromComponents<Position, Bullet>();
		mQueryBullets.m_NoneOf.AddFromComponents<PlayerTag>();

		mQueryZombies.m_Must.AddFromComponents<Position, Zombie>();
		mQueryZombies.m_NoneOf.AddFromComponents<PlayerTag>();
	}

	__inline void OnUpdate() noexcept
	{
		for (std::int16_t y = 0; y < Grid::CELL_ROW_COUNT; ++y)
		{
			for (std::int16_t x = 0; x < Grid::CELL_ROW_COUNT; ++x)
			{
				auto shareFilterPtr = findShareFilter(GridCell{ x, y });

				if (shareFilterPtr == nullptr)
				{
					continue;
				}

				Foreach(
					*shareFilterPtr, mQueryBullets,
					[&](xecs::component::entity& bulletEntity, const Position& bulletPos, const Bullet& bullet)
					{
						if (bulletEntity.isZombie())
						{
							return;
						}

						Grid::Search(
							*this, *shareFilterPtr, x, y, mQueryZombies,
							[&](xecs::component::entity& zombieEntity, const Position& zombiePos) constexpr noexcept
							{
								if (zombieEntity.isZombie())
								{
									return false;
								}

								constexpr auto distanceSq = 4 * 4;

								if ((zombiePos.mValue - bulletPos.mValue).getLengthSquared() < distanceSq)
								{
									DeleteEntity(bulletEntity);
									DeleteEntity(zombieEntity);
									return true;
								}

								return false;
							});
					});

				
			}
		}
	}

	//__inline void operator()(
	//	xecs::component::entity& entity, 
	//	const Position& bulletPos, 
	//	const Bullet& bullet)
	//{
	//	// Destroy if out of bounds
	//	if (bulletPos.x < 0 || bulletPos.x >= Grid::MAX_RESOLUTION_WIDTH 
	//	 || bulletPos.y < 0 || bulletPos.y >= Grid::MAX_RESOLUTION_HEIGHT)
	//	{
	//		DeleteEntity(entity);
	//		return;
	//	}
	//	
	//	/*Foreach(Search(mQueryZombie), 
	//		[&](xecs::component::entity& entity2, const Position& zombiePos) constexpr noexcept
	//		{
	//			if (entity2.isZombie() || entity == entity2)
	//			{
	//				return false;
	//			}

	//			constexpr auto distanceSq = 4 * 4;

	//			if ((zombiePos.mValue - bulletPos.mValue).getLengthSquared() < distanceSq)
	//			{
	//				DeleteEntity(entity);
	//				DeleteEntity(entity2);
	//				return true;
	//			}

	//			return false;
	//		});*/
	//	}
	//}

private:
	xecs::query::instance mQueryBullets{};
	xecs::query::instance mQueryZombies{};
};