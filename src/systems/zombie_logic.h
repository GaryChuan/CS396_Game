/******************************************************************************
filename: zombie_logic.h
author: Gary Chuan gary.chuan@digipen.edu
Project: CS396 Final Project
Description:
  This file contains the definition of ZombieLogic which handles the 
  deletion of "dead" zombies (health <= 0). It also triggers child systems
  such as the steering logic and update velocity in sequence.
******************************************************************************/
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

	using Update = xecs::event::instance<>;

	using events = std::tuple<Update>;

	__inline void OnGameStart() noexcept
	{
		mQueryZombies.m_Must.AddFromComponents<Zombie>();
		mQueryZombies.m_NoneOf.AddFromComponents<PlayerTag, Bullet>();
	}


	void OnUpdate() noexcept
	{
		Foreach(
			Search(mQueryZombies),
			[&](xecs::component::entity& zombieEntity, const Health& health)
			{
				if (health.mValue <= 0)
				{
					DeleteEntity(zombieEntity);
				}
			});

		SendEventFrom<Update>(this);
	}

private:
	xecs::query::instance mQueryZombies{};

};