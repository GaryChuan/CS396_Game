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

		if (pos.x < 0)
		{
			pos.x = 0;
		}
		
		if (pos.x >= Grid::MAX_RESOLUTION_WIDTH)
		{
			pos.x = Grid::MAX_RESOLUTION_WIDTH;
		}
			
		if(pos.y < 0)
		{
			pos.y = 0;
			// mBulletArchetypePtr->DestroyEntity(entity);
			// return;
		}

		if (pos.y >= Grid::MAX_RESOLUTION_HEIGHT)
		{
			pos.y = Grid::MAX_RESOLUTION_HEIGHT;
		}

		gridCell = Grid::ComputeGridCellFromWorldPosition(pos.mValue);
	}
};