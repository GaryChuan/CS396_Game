#pragma once


struct Colour
{
	float r, g, b;
};

struct Size
{
	std::uint16_t x;
	std::uint16_t y;
};

struct CharacterRenderDetails
{
	constexpr static auto typedef_v
		= xecs::component::type::share
		{
			.m_pName = "CharacterRenderDetails"
		};

	Colour mColour;
	Size mSize;
};