/******************************************************************************
filename: on_mouse_right_click.h
author: Gary Chuan gary.chuan@digipen.edu
Project: CS396 Final Project
Description:
  This file contains the definition of OnMouseRightClick which is a global
  event.
******************************************************************************/
#pragma once

struct OnMouseRightClick : xecs::event::instance<int, int>
{
	constexpr static auto typedef_v
		= xecs::event::type::global
	{
		.m_pName = "OnMouseRightClick"
	};
};