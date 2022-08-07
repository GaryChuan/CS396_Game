/******************************************************************************
filename: play_sound.h
author: Gary Chuan gary.chuan@digipen.edu
Project: CS396 Final Project
Description:
  This file contains the definition of PlaySound which is a global
  event.
******************************************************************************/
#pragma once

struct PlaySound : xecs::event::instance<const char*>
{
	constexpr static auto typedef_v
		= xecs::event::type::global
	{
		.m_pName = "PlaySound"
	};
};