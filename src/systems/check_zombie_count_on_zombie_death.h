#pragma once

struct CheckZombieCountOnZombieDeath : xecs::system::instance
{
	constexpr static auto typedef_v
		= xecs::system::type::notify_destroy
		{
			.m_pName = "CheckZombieCountOnZombieDeath"
		};

	using query = std::tuple
		<
		xecs::query::must<Zombie, ZombieGroup>,
		xecs::query::none_of<PlayerTag>
		>;

	using StartTimer = xecs::event::instance<>;

	using events = std::tuple<StartTimer>;

	CheckZombieCountOnZombieDeath(xecs::game_mgr::instance& gameMgr)
		: xecs::system::instance{ gameMgr }
	{
	}

	__inline void OnGameStart() noexcept
	{
		SendEventFrom<StartTimer>(this);
	}

	__inline void operator()(Zombie&, ZombieGroup& zombieGroup) noexcept
	{
		std::cout << zombieGroup.mID << std::endl;
	}
};