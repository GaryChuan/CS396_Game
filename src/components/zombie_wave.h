#pragma once

struct ZombieWave
{
	constexpr static auto typedef_v
		= xecs::component::type::share
	{
		.m_pName = "ZombieWave",
		.m_bBuildFilter = true
	};

	int mID{};
};