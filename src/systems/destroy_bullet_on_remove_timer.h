/******************************************************************************
filename: destroy_bullet_on_remove_timer.h
author: Gary Chuan gary.chuan@digipen.edu
Project: CS396 Final Project
Description:
  This file contains the definition of DestroyBulletOnRemoveTimer
  which handles deleting of bullet when their lifetime (timer) ends.
******************************************************************************/
#pragma once

struct DestroyBulletOnRemoveTimer : xecs::system::instance
{
	constexpr static auto typedef_v =
		xecs::system::type::notify_moved_out
	{
		.m_pName = "DestroyBulletOnRemoveTimer"
	};

	using query = std::tuple
		<
			xecs::query::must<Timer, Bullet>
		>;

	__inline void operator()(xecs::component::entity& entity) noexcept
	{
		DeleteEntity(entity);
	}
};