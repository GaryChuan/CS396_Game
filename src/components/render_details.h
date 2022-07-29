#pragma once


struct Colour
{
	float r, g, b;
};

struct Size
{
	float x;
	float y;
};

struct RenderDetails
{
	constexpr static auto typedef_v
		= xecs::component::type::share
		{
			.m_pName = "RenderDetails"
		};

	Colour mColour;
	Size mSize;
};