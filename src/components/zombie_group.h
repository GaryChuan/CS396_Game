#pragma once

struct ZombieGroup
{
	constexpr static auto typedef_v
		= xecs::component::type::share
	{
		.m_pName = "ZombieGroup",
		.m_bBuildFilter = true
	};

	int mID{};
};