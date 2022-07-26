#pragma once

struct ZombieOnDeath : xecs::system::instance
{
	constexpr static auto typedef_v
		= xecs::system::type::notify_destroy
		{
			.m_pName = "ZombieOnDeath"
		};

	using query = std::tuple
		<
			xecs::query::must<Zombie>,
			xecs::query::none_of<PlayerTag>
		>;

	ZombieOnDeath(xecs::game_mgr::instance& gameMgr)
		: xecs::system::instance { gameMgr }
	{
	}

	__inline void OnGameStart() noexcept
	{
		mParticleArchetype = &getOrCreateArchetype<ParticleArchetype>();
	}

	__inline void operator()(Position& zombiePos) noexcept
	{
		constexpr float r = 226.f / 255.f;
		constexpr float g = 174.f / 255.f;
		constexpr float b = 221.f / 255.f;

		mParticleArchetype->CreateEntities(50,
			[&](Position& particlePos, Velocity& velocity, Timer& timer, RenderDetails& renderDetails)
			{
				particlePos.mValue = zombiePos.mValue;

				velocity.mValue = UniformDiskRand(5.f);

				timer.mValue = 1.5f;

				renderDetails.mColour = Colour{ r, 0.5, b };
				renderDetails.mSize = Size{ 1, 1 };
			});
	}

private:
	xecs::archetype::instance* mParticleArchetype{};
};