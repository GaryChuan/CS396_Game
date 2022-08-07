/******************************************************************************
filename: clamp_movement.h
author: Gary Chuan gary.chuan@digipen.edu
Project: CS396 Final Project
Description:
  This file contains the definition of ClampMovement which clmaps all position
  to within the screen.
******************************************************************************/
#pragma once

struct ClampMovement : xecs::system::instance
{
	constexpr static auto typedef_v = xecs::system::type::update
	{
		.m_pName = "ClampMovement"
	};

	using query = std::tuple
		<
			xecs::query::none_of<Bullet>
		>;

	__inline void operator()(Position& pos, GridCell& gridCell) noexcept
	{
		if (pos.x < 0)
		{
			pos.x = 0;
		}

		if (pos.x >= Grid::MAX_RESOLUTION_WIDTH)
		{
			pos.x = Grid::MAX_RESOLUTION_WIDTH - 1;
		}

		if (pos.y < 0)
		{
			pos.y = 0;
		}

		if (pos.y >= Grid::MAX_RESOLUTION_HEIGHT)
		{
			pos.y = Grid::MAX_RESOLUTION_HEIGHT - 1;
		}

		gridCell = Grid::ComputeGridCellFromWorldPosition(pos.mValue);
	}
};

