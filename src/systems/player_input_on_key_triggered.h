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
		, mWeaponArsenal { InitializeWeaponArsenal() }
		, mWeaponNames { InitializeWeaponNames() }
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
				if (keys[static_cast<uint8_t>('e')])
				{
					weapon.mIndex = (++weapon.mIndex) % mWeaponArsenal.size();
					weapon.mType = mWeaponArsenal[weapon.mIndex];
					text.mValue = mWeaponNames[weapon.mIndex];
					text.mActive = true;

					AddOrRemoveComponents<std::tuple<Timer>, std::tuple<Timer>>(entity, [](Timer& timer)
						{
							timer.mValue = 0.5f;
						});
					// std::cout << "Swap weapon to " << currentWeaponIndex + 1 << std::endl;
				}
			});
	}

private:
	using WeaponArsenal = std::array<WeaponType, std::variant_size_v<WeaponType>>;
	using WeaponNames = std::array<std::string, std::variant_size_v<WeaponType>>;

	constexpr WeaponArsenal InitializeWeaponArsenal() const noexcept
	{
		return
		{
			Pistol{}, Shotgun{}, SubmachineGun{}
		};
	}

	constexpr WeaponNames InitializeWeaponNames() const noexcept
	{
		return
		{
			"Pistol", "Shotgun", "SMG"
		};
	}

private:
	
	WeaponNames mWeaponNames{};
	WeaponArsenal mWeaponArsenal{};
	xecs::query::instance mQueryPlayerOnly{};
};