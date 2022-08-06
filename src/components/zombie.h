#pragma once

struct Zombie
{
	static constexpr auto typedef_v =
		xecs::component::type::data
		{
			.m_pName = "Zombie"
		};

	enum class State
	{
		NORMAL,
		HIT
	};

	// Add zombie state here
	union
	{
		struct
		{
			float x, y;
		};

		xcore::vector2 mValue{};

	} mDesiredVelocity;

	State mState{ State::NORMAL };
};