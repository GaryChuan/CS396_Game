/******************************************************************************
filename: update_movement.h
author: Gary Chuan gary.chuan@digipen.edu
Project: CS396 Final Project
Description:
  This file contains the definition of UpdateMovement which updates
  all entity position using their velocity. It also updates the grid cell
  shared component based on updated position.
******************************************************************************/
#pragma once

struct UpdateMovement : xecs::system::instance
{
	constexpr static auto typedef_v = xecs::system::type::update
	{
		.m_pName = "UpdateMovement"
	};

	__inline void operator()(Position& pos, const Velocity& vel, GridCell& gridCell) noexcept
	{
        pos.mValue += vel.mValue;
		gridCell = Grid::ComputeGridCellFromWorldPosition(pos.mValue);
	}
};