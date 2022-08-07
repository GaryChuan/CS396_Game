/******************************************************************************
filename: player_deactivate_text_on_remove_timer.h
author: Gary Chuan gary.chuan@digipen.edu
Project: CS396 Final Project
Description:
  This file contains the definition of PlayerDeactivateTextOnRemoveTimer
  which handles deactiving reloading text when gun is finished reloading.
******************************************************************************/
#pragma once

struct PlayerDeactivateTextOnRemoveTimer : xecs::system::instance
{
	constexpr static auto typedef_v =
		xecs::system::type::notify_moved_out
	{
		.m_pName = "PlayerDeactivateTextOnRemoveTimer"
	};

	using query =
		std::tuple
		<
			xecs::query::must<Text, Timer, PlayerTag>
		>;

	__inline void operator()(Text& text) noexcept
	{
		text.mActive = false;
	}
};