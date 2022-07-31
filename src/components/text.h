#pragma once

struct Text
{
	constexpr static auto typedef_v
		= xecs::component::type::data
		{
			.m_pName = "Text"
		};

	union
	{
		struct
		{
			float x, y;
		};

		xcore::vector2 mValue{};
	} mOffset;

	enum struct Font : short
	{
		HELVETICA_10,
		HELVETICA_12,
		HELVETICA_18,
	};

	bool mActive{ true };
	Font mFont{ Font::HELVETICA_10 };
	std::string mValue{};
};