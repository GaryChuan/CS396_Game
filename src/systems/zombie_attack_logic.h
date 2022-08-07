/******************************************************************************
filename: zombie_attack_logic.h
author: Gary Chuan gary.chuan@digipen.edu
Project: CS396 Final Project
Description:
  This file contains the definition of ZombieAttackLogic which
  checks if zombie has managed to attack player.
******************************************************************************/
#pragma once

struct ZombieAttackLogic : xecs::system::instance
{
	constexpr static auto typedef_v
		= xecs::system::type::child_update<ZombieLogic, ZombieLogic::Update>
	{
		.m_pName = "ZombieAttackLogic"
	};

	using query = std::tuple
		<
			xecs::query::must<Zombie>
		>;

	ZombieAttackLogic(xecs::game_mgr::instance& gameMgr)
		: xecs::system::instance { gameMgr }
	{
	}

	__inline void OnGameStart()
	{
		mQueryPlayer.m_Must.AddFromComponents<PlayerTag>();
	}

	__inline void operator()(
		xecs::component::entity& zombieEntity, 
		const Position& zombiePos,
		const Scale& zombieScale,
		GridCell& gridCell)
	{
		auto shareFilterPtr = findShareFilter(gridCell);

		if (shareFilterPtr == nullptr)
		{
			return;
		}

		Foreach(
			*shareFilterPtr, mQueryPlayer,
			[&](
				xecs::component::entity& playerEntity,
				Health& health,
				const Position& playerPos,
				const Scale& playerScale)
			{
				if (playerPos.x < (zombiePos.x + zombieScale.x)
					&& (playerPos.x + playerScale.x) > zombiePos.x
					&& playerPos.y < (zombiePos.y + zombieScale.y)
					&& (playerPos.y + playerScale.y) > zombiePos.y)
				{
					health.mValue = std::max(0.f, health.mValue - 1);
				}

				return true;
			}
		);
	}

private:
	xecs::query::instance mQueryPlayer{};
};