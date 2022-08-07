/******************************************************************************
filename: button_logic.h
author: Gary Chuan gary.chuan@digipen.edu
Project: CS396 Final Project
Description:
  This file contains the definition of ButtonLogic which manages logic of 
  buttons such as its colour depending on the button state.
******************************************************************************/
#pragma once

struct ButtonLogic : xecs::system::instance
{
	constexpr static auto typedef_v 
		= xecs::system::type::update
		{
			.m_pName = "ButtonLogic"
		};

	using query = std::tuple
		<
			xecs::query::must<Button>
		>;

	__inline void operator()(Button& button, Colour& colour, ButtonDetails& buttonDetails) noexcept
	{
		colour.mValue = buttonDetails.mButtonColours[static_cast<int>(button.mState)];
	}
};

