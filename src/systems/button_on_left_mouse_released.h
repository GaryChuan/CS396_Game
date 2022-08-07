/******************************************************************************
filename: button_on_mouse_released.h
author: Gary Chuan gary.chuan@digipen.edu
Project: CS396 Final Project
Description:
  This file contains the definition of ButtonOnLeftMouseReleased
  which handles triggering button released state if necessary.
******************************************************************************/
#pragma once

struct ButtonOnLeftMouseReleased : xecs::system::instance
{
	constexpr static auto typedef_v
		= xecs::system::type::global_event<OnMouseLeftReleased>
	{
		.m_pName = "ButtonOnLeftMouseReleased"
	};

	ButtonOnLeftMouseReleased(xecs::game_mgr::instance& gameMgr)
		: xecs::system::instance{ gameMgr }
	{
	}

	__inline void OnGameStart() noexcept
	{
		mQueryButtons.m_Must.AddFromComponents<Button>();
	}

	void OnEvent(int mouseX, int mouseY)
	{
		Foreach(
			Search(mQueryButtons),
			[&]
		(
			const Position& pos,
			const Scale& scale,
			Colour& colour,
			Button& button
			)
			{
				const auto topLeft = pos.mValue - scale.mValue;
				const auto btmRight = pos.mValue + scale.mValue;

				if (topLeft.m_X <= mouseX && mouseX <= btmRight.m_X
					&& topLeft.m_Y <= mouseY && mouseY <= btmRight.m_Y)
				{
					button.mState = Button::State::RELEASED;
					button.mCallback();
					return true;
				}

				return false;
			}
		);
	}

private:
	xecs::query::instance mQueryButtons{};
};