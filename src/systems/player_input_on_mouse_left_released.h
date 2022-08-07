/******************************************************************************
filename: player_input_on_mouse_left_released.h
author: Gary Chuan gary.chuan@digipen.edu
Project: CS396 Final Project
Description:
  This file contains the definition of PlayerInputOnMouseLeftReleased which handles
  setting weapon to inactive when mouse is released.
******************************************************************************/
#pragma once

struct PlayerInputOnMouseLeftReleased : xecs::system::instance
{
	constexpr static auto typedef_v
		= xecs::system::type::global_event<OnMouseLeftReleased>
	{
		.m_pName = "PlayerInputOnMouseLeftReleased"
	};

	PlayerInputOnMouseLeftReleased(xecs::game_mgr::instance& gameMgr)
		: xecs::system::instance{ gameMgr }
	{
	}

	__inline void OnGameStart() noexcept
	{
		// Is there a way to store player archetype? 
		// Or do I have to query everytime an event happens
		mQueryPlayerOnly.m_Must.AddFromComponents<Position, Velocity, PlayerTag>();
		mQueryPlayerOnly.m_NoneOf.AddFromComponents<Bullet>();
	}

	void OnEvent(int mouseX, int mouseY)
	{
		Foreach(Search(mQueryPlayerOnly), [&](Weapon& weapon)
			{
				if (weapon.mState == Weapon::State::RELOAD
				 || weapon.mState == Weapon::State::RELOADING)
				{
					return;
				}

				weapon.mState = Weapon::State::INACTIVE;
			});
	}

private:

private:
	xecs::query::instance mQueryPlayerOnly{};
};