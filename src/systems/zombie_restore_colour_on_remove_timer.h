#pragma once

struct ZombieRestoreColourOnRemoveTimer : xecs::system::instance
{
	constexpr static auto typedef_v =
		xecs::system::type::notify_moved_out
	{
		.m_pName = "ZombieRestoreColourOnRemoveTimer"
	};

	using query =
		std::tuple
		<
			xecs::query::must<Timer, Zombie>
		>;

	__inline void operator()(Colour& colour) noexcept
	{
		colour.mValue = ZOMBIE_BASE_COLOUR;
	}
};