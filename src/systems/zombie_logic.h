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
		mQueryPlayer.m_Must.AddFromComponents<PlayerTag>();
	}

	__inline void operator()(const Position& zombiePos, Velocity& vel)
	{
		Foreach(Search(mQueryPlayer), 
			[&](const Position& playerPos)
			{
				vel.mValue = (playerPos.mValue - zombiePos.mValue).NormalizeSafe() * 0.5f;
			});
	}

private:
	xecs::query::instance mQueryPlayer{};
};