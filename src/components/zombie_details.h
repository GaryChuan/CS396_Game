#pragma once

struct ZombieDetails
{
	constexpr static auto typedef_v
		= xecs::component::type::share
	{
		.m_pName = "ZombieDetails"
	};

	float mMaxHealth{};
	float mMaxSpeed{};
	float mMaxAcceleration{};
};