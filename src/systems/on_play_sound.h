/******************************************************************************
filename: on_play_sound.h
author: Gary Chuan gary.chuan@digipen.edu
Project: CS396 Final Project
Description:
  This file contains the definition of ButtonOnLeftMouseClicked
  which handles triggering button pressed state if necessary.
******************************************************************************/
#pragma once

struct OnPlaySound : xecs::system::instance
{
	constexpr static auto typedef_v
		= xecs::system::type::global_event<PlaySound>
	{
		.m_pName = "OnPlaySound"
	};

	OnPlaySound(xecs::game_mgr::instance& gameMgr)
		: xecs::system::instance{ gameMgr }
	{
	}

	__inline void OnGameStart() noexcept
	{
		
	}

	void OnEvent(const char* soundName)
	{
		Service<AudioManager>::Get().PlaySound(soundName);
	}

private:
	xecs::query::instance mQueryButtons{};
};