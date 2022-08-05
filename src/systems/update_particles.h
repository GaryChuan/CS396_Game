#pragma once

struct UpdateParticles : xecs::system::instance
{
	constexpr static auto typedef_v
		= xecs::system::type::update
		{
			.m_pName = "UpdateParticles"
		};

	using query = std::tuple
		<
			xecs::query::must<ParticleTag>
		>;
	
	__inline void operator()(Position& pos, const Velocity& vel) const noexcept 
	{
		pos.mValue += vel.mValue;
	}
};