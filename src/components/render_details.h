#pragma once

struct RenderDetails
{
	constexpr static auto typedef_v
		= xecs::component::type::share
		{
			.m_pName = "RenderDetails"
		};

	/*Colour mColour;
	Size mSize;*/
};