#pragma once

struct Bullet
{
	constexpr static auto typedef_v
		= xecs::component::type::data
		{
			.m_pName = "Bullet"
		};
};