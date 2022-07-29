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

	std::string mValue{};
	bool mActive{ true };
};