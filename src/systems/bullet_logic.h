#pragma once

struct BulletLogic : xecs::system::instance
{
public:
	constexpr static auto typedef_v
		= xecs::system::type::update
	{
		.m_pName = "BulletLogic"
	};

	using ZombieHit 
		= xecs::event::instance<const Position&, const xcore::vector2&>;

	using events = std::tuple<ZombieHit>;


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
					[&](xecs::component::entity& bulletEntity, const Position& bulletPos, const Velocity& bulletVel, const Bullet& bullet)
					{
						if (bulletEntity.isZombie())
						{
							return;
						}

						Grid::Search(
							*this, *shareFilterPtr, x, y, mQueryZombies,
							[&](const xecs::component::entity& zombieEntity, Health& zombieHealth, Colour& colour, Zombie& zombie, Position& zombiePos) constexpr noexcept
							{
								if (zombieEntity.isZombie())
								{
									return false;
								}

								constexpr auto distanceSq = 4 * 4;

								if ((zombiePos.mValue - bulletPos.mValue).getLengthSquared() < distanceSq)
								{
									xcore::vector2 bulletDir = bulletVel.mValue;

									bulletDir.Normalize();

									// Spawn hit particles
									SendEventFrom<ZombieHit>(this, bulletPos, -bulletDir);

									colour.mValue = ZOMBIE_HIT_COLOUR;

									// Pushback zombie
									zombiePos.mValue += bulletDir * bullet.mPushback;
									zombieHealth.mValue -= bullet.mDamage;

									DeleteEntity(bulletEntity);
									return true;
								}

								return false;
							});
					});
			}
		}
	}

private:
	xecs::query::instance mQueryBullets{};
	xecs::query::instance mQueryZombies{};
};