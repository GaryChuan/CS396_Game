#pragma once

struct ZombieUpdateVelocity : xecs::system::instance
{
	constexpr static auto typedef_v
		= xecs::system::type::child_update<ZombieLogic, ZombieLogic::Update>
		{
			.m_pName = "ZombieUpdateVelocity"
		};

	using query = std::tuple
		<
			xecs::query::must<Zombie>
		>;

	__inline void operator()(Velocity& zombieVel, const Zombie& zombie, ZombieDetails& zombieDetails)
	{
		const auto& dVel = zombie.mDesiredVelocity.mValue;

		auto dv = dVel - zombieVel.mValue;
		auto ds = dv.getLength();

		if (ds > zombieDetails.mMaxAcceleration)
		{
			dv *= zombieDetails.mMaxAcceleration / ds;
		}

		zombieVel.mValue += dv;
	}
};