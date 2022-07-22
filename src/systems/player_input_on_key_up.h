#pragma once

struct PlayerInputOnKeyUp : xecs::system::instance
{
	constexpr static auto typedef_v
		= xecs::system::type::global_event<OnKeyUp>
	{
		.m_pName = "PlayerInputOnKeyUp"
	};

	PlayerInputOnKeyUp(xecs::game_mgr::instance& gameMgr)
		: xecs::system::instance{ gameMgr }
	{
	}

	__inline void OnGameStart() noexcept
	{
		mQueryPlayerOnly.m_Must.AddFromComponents<Position, Velocity>();
		mQueryPlayerOnly.m_NoneOf.AddFromComponents<Bullet>();
	}

	void OnEvent(const Keys& keys)
	{
		Foreach(Search(mQueryPlayerOnly), [&](Velocity& velocity)
			{
				const bool upPressed = keys[static_cast<uint8_t>('w')];
				const bool downPressed = keys[static_cast<uint8_t>('s')];
				
				if (!upPressed && !downPressed)
				{
					velocity.y = 0;
				}

				const bool leftPressed = keys[static_cast<uint8_t>('a')];
				const bool rightPressed = keys[static_cast<uint8_t>('d')];

				if (!leftPressed && !rightPressed)
				{
					velocity.x = 0;
				}
			});
	}

private:
	xecs::query::instance mQueryPlayerOnly{};
};