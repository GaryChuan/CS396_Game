/******************************************************************************
filename: colour.h
author: Gary Chuan gary.chuan@digipen.edu
Project: CS396 Final Project
Description:
  This file contains the definition of Colour component.
******************************************************************************/
#pragma once

struct Colour
{
	constexpr static auto typedef_v 
		= xecs::component::type::data
		{
			.m_pName = "Colour"
		};

	union
	{
		struct
		{
			float r, g, b;
		};

		xcore::vector3 mValue{1.f, 1.f, 1.f};
	};
};