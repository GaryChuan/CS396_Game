#pragma once

struct PlayerInputOnMouseLeftClick : xecs::system::instance
{
	constexpr static auto typedef_v
		= xecs::system::type::global_event<OnMouseLeftClick>
	{
		.m_pName = "PlayerInputOnMouseLeftClick"
	};

	PlayerInputOnMouseLeftClick(xecs::game_mgr::instance& gameMgr)
		: xecs::system::instance{ gameMgr }
	{
	}

	__inline void OnGameStart() noexcept
	{
		// Is there a way to store player archetype? 
		// Or do I have to query everytime an event happens
		mQueryPlayerOnly.m_Must.AddFromComponents<Position, Velocity, PlayerTag>();
		mQueryPlayerOnly.m_NoneOf.AddFromComponents<Bullet>();

		mBulletArchetypePtr = &getOrCreateArchetype<BulletArchetype>();
	}

	void OnEvent(int mouseX, int mouseY)
	{
		assert(mBulletArchetypePtr);

		auto& bulletArchetype = *mBulletArchetypePtr;

		Foreach(Search(mQueryPlayerOnly), [&](const Position& position)
			{
				xcore::vector2 bulletDirection
				{
					mouseX - position.x,
					mouseY - position.y
				};

				bulletDirection.NormalizeSafe();

				bulletArchetype.CreateEntity([&](Position& bulletPos, Velocity& bulletVel)
					{
						bulletPos = position;
						bulletVel.mValue = bulletDirection * 5.f;
					});
			});
	}

private:
	xecs::archetype::instance* mBulletArchetypePtr{};
	xecs::query::instance mQueryPlayerOnly{};
};