#pragma once

struct PlayerInputOnKeyDown : xecs::system::instance
{
	constexpr static auto typedef_v
		= xecs::system::type::global_event<OnKeyDown>
		{
			.m_pName = "PlayerInputOnKeyDown"
		};

	PlayerInputOnKeyDown(xecs::game_mgr::instance& gameMgr)
		: xecs::system::instance{ gameMgr }
	{
	}

	__inline void OnGameStart() noexcept
	{
		// Is there a way to store player archetype? 
		// Or do I have to query everytime an event happens
		mQueryPlayerOnly.m_Must.AddFromComponents<Position, Velocity>();
		mQueryPlayerOnly.m_NoneOf.AddFromComponents<Bullet>();
	}

	void OnEvent(const Keys& keys)
	{
		Foreach(Search(mQueryPlayerOnly), [&](Velocity& velocity)
			{
				if (keys[static_cast<uint8_t>('w')])
				{
					velocity.y = -1;
				}
				
				if (keys[static_cast<uint8_t>('s')])
				{
					velocity.y = 1;
				}

				if (keys[static_cast<uint8_t>('a')])
				{
					velocity.x = -1;
				}
				
				if (keys[static_cast<uint8_t>('d')])
				{
					velocity.x = 1;
				}

				const bool spacePressed = keys[static_cast<uint8_t>(32)];

				if (spacePressed)
				{
					std::cout << "Pew Pew" << std::endl;
				}
			});
	}

private:
	xecs::query::instance mQueryPlayerOnly{};
};