#pragma once

struct Velocity
{
	constexpr static auto typedef_v = xecs::component::type::data
	{
		.m_pName = "Velocity"
	};

	union
	{
		struct
		{
			float x;
			float y;
		};

		xcore::vector2 mValue{};
	};
};