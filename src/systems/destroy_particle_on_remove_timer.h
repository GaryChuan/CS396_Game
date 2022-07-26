#pragma once

struct DestroyParticleOnRemoveTimer : xecs::system::instance
{
	constexpr static auto typedef_v =
		xecs::system::type::notify_moved_out
		{
			.m_pName = "DestroyParticleOnRemoveTimer"
		};

	__inline void operator()(xecs::component::entity& entity) noexcept
	{
		DeleteEntity(entity);
	}
};