#pragma once

struct OnKeyUp : xecs::event::instance<const Keys&>
{
	constexpr static auto typedef_v
		= xecs::event::type::global
		{
			.m_pName = "OnKeyUp"
		};
};