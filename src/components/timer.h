#pragma once
struct Timer
{
	constexpr static auto typedef_v = xecs::component::type::data
	{
		.m_pName = "Timer"
	};

	float mValue{};
};