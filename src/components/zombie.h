#pragma once

struct Zombie
{
	static constexpr auto typedef_v =
		xecs::component::type::data
		{
			.m_pName = "Zombie"
		};

	// Add zombie state here
};