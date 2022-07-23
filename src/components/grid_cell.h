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