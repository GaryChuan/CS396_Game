/******************************************************************************
filename: on_mouse_move.h
author: Gary Chuan gary.chuan@digipen.edu
Project: CS396 Final Project
Description:
  This file contains the definition of OnMouseMove which is a global
  event.
******************************************************************************/
#pragma once

struct OnMouseMove : xecs::event::instance<int, int>
{
	constexpr static auto typedef_v
		= xecs::event::type::global
	{
		.m_pName = "OnMouseMove"
	};
};