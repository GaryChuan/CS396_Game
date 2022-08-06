#pragma once

struct SpawnParticleOnZombieHit : xecs::system::instance
{
	constexpr static auto typedef_v
		= xecs::system::type::system_event<BulletLogic, BulletLogic::ZombieHit>
		{
			.m_pName = "SpawnParticleOnZombieHit"
		};

	SpawnParticleOnZombieHit(xecs::game_mgr::instance& gameMgr)
		: xecs::system::instance{ gameMgr }
	{
	}

	__inline void OnGameStart() noexcept
	{
		mParticleArchetype = &getOrCreateArchetype<ParticleArchetype>();
	}

	__inline void OnEvent(const Position& bulletPos, const xcore::vector2& invBulletDir) noexcept
	{
		constexpr float r = 80.f / 255.f;
		constexpr float g = 226.f / 255.f;
		constexpr float b = 0.05f;

		mParticleArchetype->CreateEntities(25,
			[&](Position& particlePos, Velocity& velocity, Timer& timer, Colour& colour, Scale& scale)
			{
				auto particleDir = invBulletDir;
				
				auto randomAngle = xcore::math::DegToRad(Math::UniformRand(-50.f, 50.f));
				particleDir.Rotate(xcore::math::radian{ randomAngle });

				particlePos.mValue = bulletPos.mValue;

				velocity.mValue = particleDir * Math::UniformRand(0.05f, 4.f);

				timer.mValue = 0.15f;

				colour.mValue = xcore::vector3{ r, g, b };
				scale.mValue = xcore::vector2{ 0.5, 0.5 };
			});
	}

private:
	xecs::archetype::instance* mParticleArchetype{};
};