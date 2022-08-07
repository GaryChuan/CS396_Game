/******************************************************************************
filename: timer.h
author: Gary Chuan gary.chuan@digipen.edu
Project: CS396 Final Project
Description:
  This file contains the definition of Timer component.
******************************************************************************/
#pragma once
struct Timer
{
	constexpr static auto typedef_v = xecs::component::type::data
	{
		.m_pName = "Timer"
	};

	float mValue{};
};