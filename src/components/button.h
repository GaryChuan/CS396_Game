#pragma once

struct Button
{
	constexpr static auto typedef_v
		= xecs::component::type::data
		{
			.m_pName = "Button"
		};

	enum State
	{
		DEFAULT,
		HOVER,
		PRESSED,
		RELEASED
	};

	State mState{ State::DEFAULT };
};