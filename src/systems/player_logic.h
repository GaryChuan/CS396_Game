#pragma once

struct PlayerLogic : xecs::system::instance
{
	constexpr static auto typedef_v
		= xecs::system::type::update
		{
			.m_pName = "PlayerLogic"
		};

	using query = std::tuple
		<
			xecs::query::none_of<Bullet>
		>;

	void OnGameStart() noexcept
	{
		// mBulletArchetypePtr = &getOrCreateArchetype<bullet_archetype>();
	}

	__inline void operator()(const Position& pos)
	{
	}

private:
	// xecs::archetype::instance* mBulletArchetypePtr{};
};