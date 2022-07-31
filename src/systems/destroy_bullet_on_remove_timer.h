#pragma once

struct DestroyBulletOnRemoveTimer : xecs::system::instance
{
	constexpr static auto typedef_v =
		xecs::system::type::notify_moved_out
	{
		.m_pName = "DestroyBulletOnRemoveTimer"
	};

	using query = std::tuple
		<
			xecs::query::must<Timer, Bullet>
		>;

	__inline void operator()(xecs::component::entity& entity) noexcept
	{
		DeleteEntity(entity);
	}
};