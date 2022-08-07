/******************************************************************************
filename: button.h
author: Gary Chuan gary.chuan@digipen.edu
Project: CS396 Final Project
Description:
  This file contains the definition of Button component.
******************************************************************************/
#pragma once

struct Button
{
	constexpr static auto typedef_v
		= xecs::component::type::data
		{
			.m_pName = "Button"
		};

	enum State
	{
		DEFAULT,
		HOVERED,
		PRESSED,
		RELEASED
	};

	State mState{ State::DEFAULT };
	std::function<void()> mCallback{};
};