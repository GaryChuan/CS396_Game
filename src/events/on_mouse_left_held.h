#pragma once

struct OnMouseLeftHeld : xecs::event::instance<int, int>
{
	constexpr static auto typedef_v
		= xecs::event::type::global
	{
		.m_pName = "OnMouseLeftHeld"
	};
};