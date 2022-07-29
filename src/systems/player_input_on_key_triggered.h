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
		, mWeaponArsenal { ConstructArsenal() }
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
		Foreach(Search(mQueryPlayerOnly), [&](Weapon& weapon)
			{
				const int currentWeaponIndex = static_cast<int>(weapon.mType.index());

				if (keys[static_cast<uint8_t>('e')])
				{
					weapon.mType = mWeaponArsenal[(currentWeaponIndex + 1) % mWeaponArsenal.size()];
					std::cout << "Swap weapon to " << currentWeaponIndex + 1 << std::endl;
				}
			});
	}

private:
	using WeaponArsenal = std::array<WeaponType, std::variant_size_v<WeaponType>>;

	constexpr WeaponArsenal ConstructArsenal() const noexcept
	{
		WeaponArsenal weaponArsenal{};

		weaponArsenal[0] = Pistol{};
		weaponArsenal[1] = Shotgun{};
		weaponArsenal[2] = SubmachineGun{};

		return weaponArsenal;
	}

private:
	
	WeaponArsenal mWeaponArsenal{};
	xecs::query::instance mQueryPlayerOnly{};
};