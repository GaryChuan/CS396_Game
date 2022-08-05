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
			xecs::component::must<ParticleTag>
		>;
	
	__inline operator()(Position& pos, const Velocity& vel) const noexcept 
	{
		pos.mValue += vel.mValue;
	}
};