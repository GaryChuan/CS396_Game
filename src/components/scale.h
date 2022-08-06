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