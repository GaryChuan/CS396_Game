#pragma once

struct ZombieLogic : xecs::system::instance
{
public:
	constexpr static auto typedef_v
		= xecs::system::type::update
	{
		.m_pName = "ZombieLogic"
	};

	ZombieLogic(xecs::game_mgr::instance& gameMgr)
		: xecs::system::instance{ gameMgr }
	{
	}

	using update = xecs::event::instance<>;

	using events = std::tuple<update>;


	using query = std::tuple
		<
			xecs::query::must<Zombie>,
			xecs::query::none_of<Bullet, PlayerTag>
		>;

	void OnGameStart() noexcept
	{
		mQueryZombies.m_Must.AddFromComponents<Zombie>();
		mQueryZombies.m_NoneOf.AddFromComponents<PlayerTag, Bullet>();

		mQueryPlayer.m_Must.AddFromComponents<PlayerTag>();
	}

	void OnUpdate() noexcept
	{
		constexpr float zombieSpeed = 0.5f;
		constexpr float separationDist = 4.f;
		constexpr float separationWeight = 2.f;
		constexpr float separationDistSq = 4.f * 4.f;
		constexpr float invSeparationDist = 1.f / separationDist;

		xcore::vector2 playerPos{};

		Foreach(Search(mQueryPlayer),
			[&](const Position& position)
			{
				playerPos = position.mValue;
				// vel.mValue = (playerPos.mValue - zombiePos.mValue).NormalizeSafe() * 0.5f;
			});

		for (std::int16_t y = 0; y < Grid::CELL_ROW_COUNT; ++y)
		{
			for (std::int16_t x = 0; x < Grid::CELL_ROW_COUNT; ++x)
			{
				auto shareFilterPtr = findShareFilter(GridCell{ x, y });

				if (shareFilterPtr == nullptr)
				{
					continue;
				}

				// Steering
				Foreach(
					*shareFilterPtr, mQueryZombies,
					[&](xecs::component::entity& zombieEntity1, Zombie& zombie, Velocity& zombie1Vel, const Position& zombie1Pos)
					{
						if (zombieEntity1.isZombie())
						{
							return;
						}

						auto dVel = (playerPos - zombie1Pos.mValue).NormalizeSafe() * 0.5f;
						xcore::vector2 disp{0, 0};
						float w = 0;

						Grid::Search(
							*this, *shareFilterPtr, x, y, mQueryZombies,
							[&](xecs::component::entity& zombieEntity2, const Position& zombie2Pos) constexpr noexcept
							{
								if (zombieEntity2.isZombie())
								{
									return false;
								}

								auto diff = (zombie1Pos.mValue - zombie2Pos.mValue);
								const auto distSq = diff.getLengthSquared();

								if (distSq <= std::numeric_limits<float>::epsilon() 
								 || distSq > separationDistSq)
								{
									return false;
								}

								const float dist = std::sqrtf(distSq);
								const float weight = separationWeight * (1.f - std::powf(dist * invSeparationDist, 2));

								disp += diff * weight / dist;
								w += 1.f;

								if (w > std::numeric_limits<float>::epsilon())
								{
									dVel += disp * (1.f / w);

									const float speedSqr = dVel.getLengthSquared();
									const float desiredSqr = zombieSpeed * zombieSpeed;

									if (speedSqr > desiredSqr)
									{
										dVel *= desiredSqr / speedSqr;
									}
								}

								return false;
							});

						zombie.mDesiredVelocity.mValue = std::move(dVel);
					});
			}
		}
		
		constexpr float zombieAcceleration = 2.f;

		Foreach(Search(mQueryZombies),
			[&](Position& zombiePos, Velocity& zombieVel, const Zombie& zombie)
			{
				const float maxDelta = zombieAcceleration;
				const auto& dVel = zombie.mDesiredVelocity.mValue;

				auto dv = dVel - zombieVel.mValue;
				auto ds = dv.getLength();

				if (ds > maxDelta)
				{
					dv* maxDelta / ds;
				}

				zombieVel.mValue += dv;
				zombiePos.mValue += zombieVel.mValue;
			});
	}

private:
	xecs::query::instance mQueryZombies{};
	xecs::query::instance mQueryPlayer{};
};