#pragma once

struct Zombie
{
	static constexpr auto typedef_v =
		xecs::component::type::data
		{
			.m_pName = "Zombie"
		};

	// Add zombie state here
	union
	{
		struct
		{
			float x, y;
		};

		xcore::vector2 mValue{};

	} mDesiredVelocity;
};