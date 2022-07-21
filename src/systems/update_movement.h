#pragma once

struct UpdateMovement : xecs::system::instance
{
	constexpr static auto typedef_v = xecs::system::type::update
	{
		.m_pName = "UpdateMovement"
	};

	__inline void operator()(Position& pos, Velocity& vel) noexcept
	{
        pos.mValue += vel.mValue;

        // Bounce on edges
        if (pos.x < 0)
        {
            pos.x = 0;
            vel.x = -vel.x;
        }
        else if (pos.x >= 1024)
        {
            pos.x = 1024 - 1;
            vel.x = -vel.x;
        }

        if (pos.y < 0)
        {
            pos.y = 0;
            vel.y = -vel.y;
        }
        else if (pos.y >= 800)
        {
            pos.y = 800 - 1;
            vel.y = -vel.y;
        }
	}
};