#pragma once

struct BulletLogic : xecs::system::instance
{
public:
	constexpr static auto typedef_v
		= xecs::system::type::update
	{
		.m_pName = "BulletLogic"
	};

	BulletLogic(xecs::game_mgr::instance& gameMgr)
		: xecs::system::instance{ gameMgr }
	{
	}


	using query = std::tuple
		<
			xecs::query::must<Bullet>
		>;

	void OnGameStart() noexcept
	{
		mBulletArchetypePtr = &getOrCreateArchetype<BulletArchetype>();
	}

	__inline void operator()(
		xecs::component::entity& entity, 
		const Position& pos, 
		const Bullet& bullet)
	{
		// Destroy if out of bounds
		if (pos.x < 0 || pos.x >= 1024 || pos.y < 0 || pos.y >= 800)
		{
			mBulletArchetypePtr->DestroyEntity(entity);
		}
	}

private:
	xecs::archetype::instance* mBulletArchetypePtr{};
};