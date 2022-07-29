#pragma once

struct PlayerDeactivateTextOnRemoveTimer : xecs::system::instance
{
	constexpr static auto typedef_v =
		xecs::system::type::notify_moved_out
	{
		.m_pName = "PlayerDeactivateTextOnRemoveTimer"
	};

	using query =
		std::tuple
		<
			xecs::query::must<Text, Timer, PlayerTag>
		>;

	__inline void operator()(Text& text) noexcept
	{
		text.mActive = false;
	}
};