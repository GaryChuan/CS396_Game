#pragma once

struct ButtonLogic : xecs::system::instance
{
	constexpr static auto typedef_v 
		= xecs::system::type::update
		{
			.m_pName = "ButtonLogic"
		};

	using query = std::tuple
		<
			xecs::query::must<Button>,
			xecs::query::none_of<Zombie>
		>;

	__inline void operator()(Button& button, Colour& colour, ButtonDetails& buttonDetails) noexcept
	{
		colour.mValue = buttonDetails.mButtonColours[static_cast<int>(button.mState)];
	}
};

