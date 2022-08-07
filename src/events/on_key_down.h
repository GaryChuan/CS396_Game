/******************************************************************************
filename: on_key_down.h
author: Gary Chuan gary.chuan@digipen.edu
Project: CS396 Final Project
Description:
  This file contains the definition of OnKeyDown which is a global
  event.
******************************************************************************/
#pragma once

struct OnKeyDown : xecs::event::instance<const Keys&>
{
	constexpr static auto typedef_v
		= xecs::event::type::global
		{
			.m_pName = "OnKeyDown"
		};
};