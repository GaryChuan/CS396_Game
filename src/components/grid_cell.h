/******************************************************************************
filename: grid_cell.h
author: Gary Chuan gary.chuan@digipen.edu
Project: CS396 Final Project
Description:
  This file contains the definition of the GridCell share component.
******************************************************************************/
#pragma once

struct GridCell
{
	constexpr static auto typedef_v
		= xecs::component::type::share
		{
			.m_pName = "GridCell",
			.m_bBuildFilter = true
		};

	std::int16_t x;
	std::int16_t y;
};