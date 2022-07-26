#pragma once

struct UpdateTimer : xecs::system::instance
{
	constexpr static auto typedef_v =
		xecs::system::type::update
		{
			.m_pName = "UpdateTimer"
		};

	__inline void operator()(xecs::component::entity& entity, Timer& timer)
	{
		constexpr float delta = 1 / 60.f;

		timer.mValue -= delta;

		if (timer.mValue <= 0)
		{
			(void)AddOrRemoveComponents<std::tuple<>, std::tuple<Timer>>(entity);
		}
	}
};