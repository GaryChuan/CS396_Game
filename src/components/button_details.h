/******************************************************************************
filename: button_details.h
author: Gary Chuan gary.chuan@digipen.edu
Project: CS396 Final Project
Description:
  This file contains the definition of the ButtonDetails share component.
******************************************************************************/
#pragma once

struct ButtonDetails
{
	constexpr static auto typedef_v
		= xecs::component::type::share
		{
			.m_pName = "ButtonDetails",
			.m_bBuildFilter = true
		};

	std::array<xcore::vector3, 4> mButtonColours
	{
		BUTTON_DEFAULT_COLOUR,
		BUTTON_HOVER_COLOUR,
		BUTTON_PRESSED_COLOUR,
		BUTTON_RELEASED_COLOUR
	};
};