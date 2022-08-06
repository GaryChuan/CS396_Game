#pragma once

struct Text
{
	constexpr static auto typedef_v
		= xecs::component::type::data
		{
			.m_pName = "Text"
		};

	enum struct Font : short
	{
		HELVETICA_10,
		HELVETICA_12,
		HELVETICA_18,
	};

	union
	{
		struct
		{
			float x, y;
		};

		xcore::vector2 mValue{};
	} mOffset;

	union
	{
		struct
		{
			float r, g, b;
		};

		xcore::vector3 mValue{1.f, 1.f, 1.f};
	} mColour;

	bool mActive{ true };
	Font mFont{ Font::HELVETICA_10 };
	std::string mValue{};
};