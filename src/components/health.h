#pragma once

struct Health
{
	constexpr static auto typedef_v 
		= xecs::component::type::data
		{
			.m_pName = "Health"
		};

	float mValue;
};