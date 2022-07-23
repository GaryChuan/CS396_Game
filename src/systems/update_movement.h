#pragma once

struct UpdateMovement : xecs::system::instance
{
	constexpr static auto typedef_v = xecs::system::type::update
	{
		.m_pName = "UpdateMovement"
	};

	__inline void operator()(Position& pos, Velocity& vel, GridCell& gridCell) noexcept
	{
        pos.mValue += vel.mValue;
		gridCell = Grid::ComputeGridCellFromWorldPosition(pos.mValue);
	}
};