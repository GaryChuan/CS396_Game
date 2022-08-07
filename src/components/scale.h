/******************************************************************************
filename: scale.h
author: Gary Chuan gary.chuan@digipen.edu
Project: CS396 Final Project
Description:
  This file contains the definition of Scale component.
******************************************************************************/
#pragma once

struct Scale
{
	constexpr static auto typedef_v
		= xecs::component::type::data
		{
			.m_pName = "Scale"
		};

	union
	{
		struct
		{
			float x, y;
		};

		xcore::vector2 mValue{};
	};
};