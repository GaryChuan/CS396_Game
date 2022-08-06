#pragma once

struct ButtonDetails
{
	constexpr static auto typedef_v
		= xecs::component::type::share
		{
			.m_pName = "ButtonDetails",
			.m_bBuildFilter = true
		};

	std::array<xcore::vector3, 4> mButtonColours
	{
		BUTTON_DEFAULT_COLOUR,
		BUTTON_HOVER_COLOUR,
		BUTTON_PRESSED_COLOUR,
		BUTTON_RELEASED_COLOUR
	};
};