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
		xcore::vector2 playerPos{};

		Foreach(Search(mQueryPlayer),
			[&](const Position& position)
			{
				playerPos = position.mValue;
				// vel.mValue = (playerPos.mValue - zombiePos.mValue).NormalizeSafe() * 0.5f;
			});

		Foreach(Search(mQueryZombies),
			[&](xecs::component::entity& zombie1, Velocity& zombieVel, const Position& zombiePos) noexcept
			{
				Foreach(
					Search(mQueryZombies),
					[&](xecs::component::entity& zombie2, const Position& zombiePos2)
					{
						if (zombie2.isZombie()
						 || zombie1 == zombie2)
						{
							return;
						}



					});

				zombieVel.mValue = (playerPos - zombiePos.mValue).NormalizeSafe() * 0.5f;
			});
	}

private:
	xecs::query::instance mQueryZombies{};
	xecs::query::instance mQueryPlayer{};
};