#pragma once

struct Health
{
	constexpr static auto typedef_v = xecs::component::type::data{};

	float mValue;
};