/******************************************************************************
filename: zombie_restore_colour_on_remove_timer.h
author: Gary Chuan gary.chuan@digipen.edu
Project: CS396 Final Project
Description:
  This file contains the definition of ZombieRestoreColourOnRemoveTimer
  which handles the restoring of zombie colour when timer gets removed.
******************************************************************************/
#pragma once

struct ZombieRestoreColourOnRemoveTimer : xecs::system::instance
{
	constexpr static auto typedef_v =
		xecs::system::type::notify_moved_out
	{
		.m_pName = "ZombieRestoreColourOnRemoveTimer"
	};

	using query =
		std::tuple
		<
			xecs::query::must<Timer, Zombie>
		>;

	__inline void operator()(Colour& colour) noexcept
	{
		colour.mValue = ZOMBIE_BASE_COLOUR;
	}
};