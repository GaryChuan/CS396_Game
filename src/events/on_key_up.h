/******************************************************************************
filename: on_key_up.h
author: Gary Chuan gary.chuan@digipen.edu
Project: CS396 Final Project
Description:
  This file contains the definition of OnKeyUp which is a global
  event.
******************************************************************************/
#pragma once

struct OnKeyUp : xecs::event::instance<const Keys&>
{
	constexpr static auto typedef_v
		= xecs::event::type::global
		{
			.m_pName = "OnKeyUp"
		};
};