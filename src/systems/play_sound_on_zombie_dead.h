/******************************************************************************
filename: play_sound_on_zombie_dead.h
author: Gary Chuan gary.chuan@digipen.edu
Project: CS396 Final Project
Description:
  This file contains the definition of OnZombieDead
  which handles playing of zombie dead sound.
******************************************************************************/
#pragma once

struct PlaySoundOnZombieDead : xecs::system::instance
{
	constexpr static auto typedef_v =
		xecs::system::type::notify_destroy
	{
		.m_pName = "PlaySoundOnZombieDead"
	};

	using query = std::tuple
		<
			xecs::query::must<Zombie>
		>;

	__inline void operator()(xecs::component::entity&) noexcept
	{
		SendGlobalEvent<PlaySound>(ZOMBIE_DEAD_SOUND, ZOMBIE_DEAD_SOUND_VOL);
	}
};