#pragma once

struct PlayerInputOnKeyTriggered : xecs::system::instance
{
	constexpr static auto typedef_v
		= xecs::system::type::global_event<OnKeyDown>
	{
		.m_pName = "PlayerInputOnKeyTriggered"
	};

	PlayerInputOnKeyTriggered(xecs::game_mgr::instance& gameMgr)
		: xecs::system::instance{ gameMgr }
	{
	}

	__inline void OnGameStart() noexcept
	{
		// Is there a way to store player archetype? 
		// Or do I have to query everytime an event happens
		mQueryPlayerOnly.m_Must.AddFromComponents<Position, PlayerTag>();
		mQueryPlayerOnly.m_NoneOf.AddFromComponents<Bullet>();
	}

	void OnEvent(const Keys& keys)
	{
		Foreach(Search(mQueryPlayerOnly), [&](xecs::component::entity& entity, Weapon& weapon, Text& text)
			{
				if (weapon.mState == Weapon::State::RELOADING 
				 || weapon.mState == Weapon::State::RELOAD)
				{
					return;
				}

				int weaponSelected = -1;

				for (int i = 0; i < weapon.mArsenal.size(); ++i)
				{
					const auto keyIndex = static_cast<uint8_t>('0' + (i + 1));
					
					if(keys[keyIndex])
					{
						weaponSelected = i;
						break;
					}
				}

				if (weaponSelected != -1)
				{
					weapon.mCurrentWeapon = static_cast<Weapon::Type>(weaponSelected);
					text.mValue = Weapon::names[weaponSelected];
					text.mActive = true;

					AddOrRemoveComponents<std::tuple<Timer>, std::tuple<Timer>>(
						entity, [](Timer& timer)
						{
							timer.mValue = 0.5f;
						});
				}

			});
	}

private:
	xecs::query::instance mQueryPlayerOnly{};
};